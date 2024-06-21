#include "../../Header/Mode/ModeSelectPlayer.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Object/Stage/Stage.h"
#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/UI/Base/UIRotaBase.h"
#include "../../Header/Manager/UIManager.h"
ModeSelectPlayer::ModeSelectPlayer() {
	_superManager = SuperManager::GetInstance();
	_playerManager = nullptr;
};

ModeSelectPlayer::~ModeSelectPlayer() {

};

bool ModeSelectPlayer::Initialize() {
	_playerManager = NEW PlayerManager();
	ObjectManager* objectManager = dynamic_cast<ObjectManager*>(_superManager->GetManager("objectManager"));
	//ステージの生成
	objectManager->Add("Stage", NEW Stage("Stage"));

	//コントローラーと同じ数になるまで追加する
	for (int i = 0; i < GetJoypadNum(); i++) {
		_playerParam.push_back(std::make_tuple("",NEW XInput(), 0));
		_selectCharacter.push_back(std::make_pair(false, 0));
		UIBase* uiRota = NEW UIBase(Vector3D(0,0,0), 0.5f,255,0);
		dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"))->Add("CheckUI_" + std::to_string(i), i, uiRota);
		_ui.push_back(uiRota);
	}
	// モデルの読み込み
	std::string name[4] = {"Cat","Fox","Kappa","Rabbit"};
	for (int i = 0; i < 4; i++){
		std::string modelPath = "Res/Model/Player/" + name[i] + ".mv1";
		int model = ResourceServer::MV1LoadModel(name[i],modelPath.c_str());
		MV1SetScale(model, VScale(VGet(1.0f, 1.0f, 1.0f), 30.0f));
		_modelParam.push_back(std::make_pair(name[i],model));
	}

	_graphHandle["yes"] = LoadGraph("Res/YES.png");
	_graphHandle["no"] = LoadGraph("Res/NO.png");
	
	SetCameraPositionAndTarget_UpVecY(VGet(0, 800, -2000), VGet(0, 0, 0));
	return true;
};

bool ModeSelectPlayer::Terminate(){
	UIManager* uiManager = dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"));
	for(int deleteNum = XInput::GetConnectNum(); deleteNum > 0; deleteNum-- ){
		uiManager->Del("CheckUI_" + std::to_string(deleteNum - 1));
	}
	return true;
};

bool ModeSelectPlayer::PlayerNumAdjust(){
	int connectNum = XInput::GetConnectNum();
	int controllerNum = GetJoypadNum();
	// プレイヤー数がコントローラーと違う場合
	if(controllerNum != connectNum){
		// プレイヤー数がコントローラーより少ない場合
		if (controllerNum > connectNum) {
			//コントローラーと同じ数になるまで追加する
			for (int i = connectNum; i < controllerNum; i++) {
				_playerParam.push_back(std::make_tuple("",NEW XInput(), 0));
				_selectCharacter.push_back(std::make_pair(false,0));
				UIBase* uiRota = NEW UIBase(Vector3D(0, 0, 0), 0.5f, 255, 0);
				dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"))->Add("CheckUI_" + std::to_string(i), i, uiRota);
				_ui.push_back(uiRota);
			}
		}
		// プレイヤー数がコントローラーより多い場合
		else {
			// コントローラーと同じ数になるまで削除する
			for (int i = connectNum; i > controllerNum; i--) {
				delete std::get<1>(_playerParam[i-1]);
				_playerParam.pop_back();
				_selectCharacter.pop_back();
				XInput::SetConnectNum(controllerNum);
				dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"))->Del("CheckUI_" + std::to_string(i-1));
				_ui.pop_back();
			}
		}
		XInput::ReSet();
	}
	return true;
};

bool ModeSelectPlayer::PlayerSelect(){
	for (int i = 0; i < _playerParam.size(); i++) {

		// コントローラーの更新
		XInput* input = std::get<1>(_playerParam[i]);
		input->Input();

		// キャラクターの選択
		if(!_selectCharacter[i].first){
			if(input->GetTrg(XINPUT_BUTTON_STICK_RIGHT)){
				_selectCharacter[i].second = (4 + _selectCharacter[i].second + 1) % 4;
			}
			else if(input->GetTrg(XINPUT_BUTTON_STICK_LEFT)){
				_selectCharacter[i].second = (4 + _selectCharacter[i].second - 1) % 4;
			}
		}

		// 選択終了・解除
		if (input->GetTrg(XINPUT_BUTTON_B)) {
			if(_selectCharacter[i].first){
			    // 選択したキャラクターを使用しているか？
			    _selectCharacter[i].first = !_selectCharacter[i].first;
				std::get<2>(_playerParam[i]) = 0;
			}
			else{
				// 選択したキャラクターを使用しているか？
				bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [&](std::pair<bool, int> value) { 
					if (!value.first)return true;
					return _selectCharacter[i].second != value.second; });
				// すべてのプレイヤーが選択していない場合
				if (allTrue) {
					_selectCharacter[i].first = !_selectCharacter[i].first;
					std::get<0>(_playerParam[i]) = _modelParam[_selectCharacter[i].second].first;
					std::get<2>(_playerParam[i]) = _modelParam[_selectCharacter[i].second].second;
				}
			}
		}
	}
	// すべてのプレイヤーが選択を終了しているか？
	bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [](std::pair<bool, int> value) { return value.first; });


	// デバッグ時はプレイヤーが1人以上いる場合
	if (allTrue) {

	// 本番時はすべてのプレイヤーが選択を終了しているかつプレイヤーが2人以上いる場合
	//if (allTrue && _playerParam.size() > 1) {

		for (int i = 0; i < _playerParam.size(); i++) {
			//誰かがBボタンを押したときに次に進む
			if(std::get<1>(_playerParam[i])->GetTrg(XINPUT_BUTTON_A)){
				// プレイヤーの生成
				_playerManager->Add(_playerParam);
				_superManager->Add("playerManager",5,_playerManager);
				// モードの変更
				ModeServer::GetInstance()->Add(NEW ModeGame(), 1, "ModeGame");
				ModeServer::GetInstance()->Del(this);
				break;
			}
		}
	}
	return true;
};

bool ModeSelectPlayer::Process(){
	ModeBase::Process();

	// プレイヤー数の調整
	PlayerNumAdjust();
	// プレイヤーの選択
	PlayerSelect();
	return true;
};

bool ModeSelectPlayer::Render(){

	int playerNum = _playerParam.size();

	for(int i = 0; i < playerNum; i++) {
		Vector3D modelPos;
		int modelHandle = _modelParam[_selectCharacter[i].second].second;
		int graphHandle = (_selectCharacter[i].first) ? _graphHandle["yes"] : _graphHandle["no"];
		if(playerNum > 1){
			// プレイヤーが複数の場合　等間隔
			float dis = 500.0f;
			float length = dis / (playerNum - 1);
			modelPos = Vector3D(-dis / 2 + length * i, 0, 0);
		}
		// モデルの描画
		MV1SetPosition(modelHandle, modelPos.toVECTOR());
		MV1DrawModel(modelHandle);


		Vector3D handlePos = ConvWorldPosToScreenPos(modelPos.toVECTOR());
		_ui[i]->SetPos(handlePos + Vector3D(0,50,0));
		_ui[i]->SetHandle(graphHandle);
		//DrawRotaGraph(handlePos.x, handlePos.y,1.0f,0.0f,graphHandle,true);


		printfDx("\n\nPlayer%d : %s",i+1,(_selectCharacter[i].first) ? "選択完了" : "選択中");
	}
	return true;
};
