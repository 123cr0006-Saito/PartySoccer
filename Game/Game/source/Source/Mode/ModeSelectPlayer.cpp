#include "../../Header/Mode/ModeSelectPlayer.h"
#include "../../Header/Mode/ModeGame.h"
#include "../MemoryLeak.h"

ModeSelectPlayer::ModeSelectPlayer() {
	_superManager = SuperManager::GetInstance();
	_playerManager = nullptr;
};

ModeSelectPlayer::~ModeSelectPlayer() {

};

bool ModeSelectPlayer::Initialize() {
	_playerManager = NEW PlayerManeger();

	//コントローラーと同じ数になるまで追加する
	for (int i = 0; i < GetJoypadNum(); i++) {
		_playerParam.push_back(std::make_pair(NEW XInput(), 0));
		_selectCharacter.push_back(std::make_pair(false, 0));
	}

	// モデルの読み込み
	std::string path[4] = {"Cat/cat","Fox/fox","Kappa/kappa","Rabbit/rabbit"};
	for (int i = 0; i < 4; i++){
		std::string modelPath = "Res/Model/Player/" + path[i] + ".mv1";
		_modelHandle[i] = MV1LoadModel(modelPath.c_str());
	}

	VECTOR pos[4] = {VGet(0,0,0),VGet(1920,0,0),VGet(0,1080,0),VGet(1920,1080,0)};
	std::pair<int,int> uv[4] = {std::make_pair(0,0),std::make_pair(1,0),std::make_pair(0,1),std::make_pair(1,1)};
	for(int i = 0; i < 4; i++){
		_vertex[i].dif = GetColorU8(255, 255, 255, 255);
		_vertex[i].pos = pos[i];
		_vertex[i].rhw = 1.0f;
		_vertex[i].u = uv[i].first;
		_vertex[i].v = uv[i].second;
	}
	_scrollSpeed = 5;
	textureHandle = LoadGraph("Res/Grass_col.JPG");
	return true;
};

bool ModeSelectPlayer::Terminate(){
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
				_playerParam.push_back(std::make_pair(NEW XInput(),0));
				_selectCharacter.push_back(std::make_pair(false,0));
			}
		}
		// プレイヤー数がコントローラーより多い場合
		else {
			// コントローラーと同じ数になるまで削除する
			for (int i = connectNum; i > controllerNum; i--) {
				delete _playerParam[i-1].first;
				_playerParam.pop_back();
				_selectCharacter.pop_back();
				XInput::SetConnectNum(controllerNum);
			}
		}
		XInput::ReSet();
	}
	return true;
};

bool ModeSelectPlayer::PlayerSelect(){
	for (int i = 0; i < _playerParam.size(); i++) {

		// コントローラーの更新
		_playerParam[i].first->Input();

		
		// キャラクターの選択
		if(!_selectCharacter[i].first){
			if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_RIGHT)){
				_selectCharacter[i].second = (4 + _selectCharacter[i].second + 1) % 4;
			}
			else if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_LEFT)){
				_selectCharacter[i].second = (4 + _selectCharacter[i].second - 1) % 4;
			}
		}


		// 選択終了・解除
		if (_playerParam[i].first->GetTrg(XINPUT_BUTTON_B)) {
			if(_selectCharacter[i].first){
			    // 選択したキャラクターを使用しているか？
			    bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [&](std::pair<bool, int> value) { return value.second  != _playerParam[i].second;});
			    // すべてのプレイヤーが選択していない場合
			    if(allTrue){
			        _selectCharacter[i].first = !_selectCharacter[i].first;
			    }
			}
			else{
				_selectCharacter[i].first = !_selectCharacter[i].first;
				_playerParam[i].second = _modelHandle[_selectCharacter[i].second];
			}
		}
	}
	// すべてのプレイヤーが選択を終了しているか？
	bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [](std::pair<bool, int> value) { return value.first; });

	if(allTrue){
		for (int i = 0; i < _playerParam.size(); i++) {
			//誰かがBボタンを押したときに次に進む
			if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_A)){
				// プレイヤーの生成
				_playerManager->Add(_playerParam);
				_superManager->AddManager("playerManager",2,_playerManager);
				// モードの変更
				ModeServer::GetInstance()->Add(NEW ModeGame(), 1, "Main");
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

	// カメラの設定
	SetupCamera_Ortho(100);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -100), VGet(0, 0, 0));
	return true;
};

bool ModeSelectPlayer::Render(){
	int playerNum = _playerParam.size();
	unsigned short textureIndex[6] = {0,1,2,2,1,3};
	DrawPrimitiveIndexed2D(_vertex.data(), 4, textureIndex, 6, DX_PRIMTYPE_TRIANGLELIST, textureHandle, TRUE);

	for(int i = 0; i < playerNum; i++) {
		if(playerNum == 1){
			// プレイヤーが一人の場合　中心
			MV1SetPosition(_modelHandle[_selectCharacter[i].second], VGet(0, 0, 0));
		}
		else{
			// プレイヤーが複数の場合　等間隔
			float dis = 100.0f;
			float length = dis / (playerNum - 1);
		    MV1SetPosition(_modelHandle[_selectCharacter[i].second], VGet(-dis/2 + length * i, 0, 0));
		}
		// モデルの描画
		MV1DrawModel(_modelHandle[_selectCharacter[i].second]);
		printfDx("\n\nPlayer%d : %s",i+1,(_selectCharacter[i].first) ? "選択完了" : "選択中");
	}
	return true;
};
