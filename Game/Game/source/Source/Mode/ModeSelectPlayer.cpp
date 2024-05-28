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

	//�R���g���[���[�Ɠ������ɂȂ�܂Œǉ�����
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
	// �v���C���[�����R���g���[���[�ƈႤ�ꍇ
	if(playerNum != controllerNum){
		// �v���C���[�����R���g���[���[��菭�Ȃ��ꍇ
		if (playerNum < controllerNum) {
			//�R���g���[���[�Ɠ������ɂȂ�܂Œǉ�����
			for (int i = playerNum; i < controllerNum; i++) {
				_playerParam.push_back(std::make_pair(NEW XInput(),0));
				_selectCharacter.push_back(std::make_pair(false,-1));
			}
		}
		// �v���C���[�����R���g���[���[��葽���ꍇ
		else {
			// �R���g���[���[�Ɠ������ɂȂ�܂ō폜����
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

		// �R���g���[���[�̍X�V
		_playerParam[i].first->Input();

		// �L�����N�^�[�̑I��
		if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_RIGHT)){
			_playerParam[i].second = (4 + _playerParam[i].second + 1) % 4;
		}
		else if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_LEFT)){
			_playerParam[i].second = (4 + _playerParam[i].second - 1) % 4;
		}


		// �I���I���E����
		if (_playerParam[i].first->GetTrg(XINPUT_BUTTON_B)) {
			if(_selectCharacter[i].first){
			    // �I�������L�����N�^�[���g�p���Ă��邩�H
			    bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [&](std::pair<bool, int> value) { return value.second  != _playerParam[i].second;});
			    // ���ׂẴv���C���[���I�����Ă��Ȃ��ꍇ
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
	// ���ׂẴv���C���[���I�����I�����Ă��邩�H
	bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [](std::pair<bool, int> value) { return value.first; });

	if(allTrue){
		for (int i = 0; i < _playerParam.size(); i++) {
			//�N����B�{�^�����������Ƃ��Ɏ��ɐi��
			if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_B)){
				// �v���C���[�̐���
				_playerManeger->Add(_playerParam);
				// ���[�h�̕ύX
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
	// �v���C���[���̒���
	PlayerNumAdjust();
	// �v���C���[�̑I��
	PlayerSelect();
	// �R���g���[���[�̐����X�V
	XInput::UpdateJoyPad();
	return true;
};

bool ModeSelectPlayer::Render(){

	return true;
};
