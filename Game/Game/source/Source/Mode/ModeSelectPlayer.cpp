#include "../../Header/Mode/ModeSelectPlayer.h"
#include "../../Header/Mode/ModeGame.h"
#include "../MemoryLeak.h"

ModeSelectPlayer::ModeSelectPlayer(){
	_superManager = SuperManager::GetInstance();
};

ModeSelectPlayer::~ModeSelectPlayer(){
	
};

bool ModeSelectPlayer::Initialize(){
	_playerManeger = NEW PlayerManeger();

	//コントローラーと同じ数になるまで追加する
	for (int i = 0; i < GetJoypadNum(); i++) {
			_playerParam.push_back(std::make_pair(NEW XInput(), 0));
	}

	return true;
};

bool ModeSelectPlayer::Terminate(){
	return true;
};

bool ModeSelectPlayer::PlayerNumAdjust(){
	int playerNum = _playerParam.size();
	int controllerNum = XInput::GetConnectNum();
	// プレイヤー数がコントローラーと違う場合
	if(playerNum != controllerNum){
		// プレイヤー数がコントローラーより少ない場合
		if (playerNum < controllerNum) {
			//コントローラーと同じ数になるまで追加する
			for (int i = playerNum; i < controllerNum; i++) {
				_playerParam.push_back(std::make_pair(NEW XInput(),0));
				_selectCharacter.push_back(std::make_pair(false,-1));
			}
		}
		// プレイヤー数がコントローラーより多い場合
		else {
			// コントローラーと同じ数になるまで削除する
			for (int i = playerNum; i > controllerNum; i--) {
				delete _playerParam[i-1].first;
				_playerParam.pop_back();
				_selectCharacter.pop_back();
			}
		}
	}
	return true;
};

bool ModeSelectPlayer::PlayerSelect(){
	for (int i = 0; i < _playerParam.size(); i++) {

		// コントローラーの更新
		_playerParam[i].first->Input();

		// キャラクターの選択
		if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_RIGHT)){
			_playerParam[i].second = (4 + _playerParam[i].second + 1) % 4;
		}
		else if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_LEFT)){
			_playerParam[i].second = (4 + _playerParam[i].second - 1) % 4;
		}


		// 選択終了・解除
		if (_playerParam[i].first->GetTrg(XINPUT_BUTTON_B)) {
			if(_selectCharacter[i].first){
			    // 選択したキャラクターを使用しているか？
			    bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [&](std::pair<bool, int> value) { return value.second  != _playerParam[i].second;});
			    // すべてのプレイヤーが選択していない場合
			    if(allTrue){
			        _selectCharacter[i].first = !_selectCharacter[i].first;
			        _selectCharacter[i].second = _playerParam[i].second;
			    }
			}
			else{
				_selectCharacter[i].first = !_selectCharacter[i].first;
				_selectCharacter[i].second = -1;
			}
		}
	}
	// すべてのプレイヤーが選択を終了しているか？
	bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [](std::pair<bool, int> value) { return value.first; });

	if(allTrue){
		for (int i = 0; i < _playerParam.size(); i++) {
			//誰かがBボタンを押したときに次に進む
			if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_B)){
				// プレイヤーの生成
				_playerManeger->Add(_playerParam);
				// モードの変更
				ModeServer::GetInstance()->Add(NEW ModeGame(), 1, "Main");
				ModeServer::GetInstance()->Del(this);
				break;
			}
		}
		_superManager->AddManager(0,_playerManeger);
	}
	return true;
};

bool ModeSelectPlayer::Process(){
	ModeBase::Process();
	// プレイヤー数の調整
	PlayerNumAdjust();
	// プレイヤーの選択
	PlayerSelect();
	// コントローラーの数を更新
	XInput::UpdateJoyPad();
	return true;
};

bool ModeSelectPlayer::Render(){

	return true;
};
