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

	//�R���g���[���[�Ɠ������ɂȂ�܂Œǉ�����
	for (int i = 0; i < GetJoypadNum(); i++) {
		_playerParam.push_back(std::make_pair(NEW XInput(), 0));
		_selectCharacter.push_back(std::make_pair(false, 0));
	}

	// ���f���̓ǂݍ���
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
	// �v���C���[�����R���g���[���[�ƈႤ�ꍇ
	if(controllerNum != connectNum){
		// �v���C���[�����R���g���[���[��菭�Ȃ��ꍇ
		if (controllerNum > connectNum) {
			//�R���g���[���[�Ɠ������ɂȂ�܂Œǉ�����
			for (int i = connectNum; i < controllerNum; i++) {
				_playerParam.push_back(std::make_pair(NEW XInput(),0));
				_selectCharacter.push_back(std::make_pair(false,0));
			}
		}
		// �v���C���[�����R���g���[���[��葽���ꍇ
		else {
			// �R���g���[���[�Ɠ������ɂȂ�܂ō폜����
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

		// �R���g���[���[�̍X�V
		_playerParam[i].first->Input();

		
		// �L�����N�^�[�̑I��
		if(!_selectCharacter[i].first){
			if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_RIGHT)){
				_selectCharacter[i].second = (4 + _selectCharacter[i].second + 1) % 4;
			}
			else if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_STICK_LEFT)){
				_selectCharacter[i].second = (4 + _selectCharacter[i].second - 1) % 4;
			}
		}


		// �I���I���E����
		if (_playerParam[i].first->GetTrg(XINPUT_BUTTON_B)) {
			if(_selectCharacter[i].first){
			    // �I�������L�����N�^�[���g�p���Ă��邩�H
			    bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [&](std::pair<bool, int> value) { return value.second  != _playerParam[i].second;});
			    // ���ׂẴv���C���[���I�����Ă��Ȃ��ꍇ
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
	// ���ׂẴv���C���[���I�����I�����Ă��邩�H
	bool allTrue = std::all_of(_selectCharacter.begin(), _selectCharacter.end(), [](std::pair<bool, int> value) { return value.first; });

	if(allTrue){
		for (int i = 0; i < _playerParam.size(); i++) {
			//�N����B�{�^�����������Ƃ��Ɏ��ɐi��
			if(_playerParam[i].first->GetTrg(XINPUT_BUTTON_A)){
				// �v���C���[�̐���
				_playerManager->Add(_playerParam);
				_superManager->AddManager("playerManager",2,_playerManager);
				// ���[�h�̕ύX
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
	// �v���C���[���̒���
	PlayerNumAdjust();
	// �v���C���[�̑I��
	PlayerSelect();

	// �J�����̐ݒ�
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
			// �v���C���[����l�̏ꍇ�@���S
			MV1SetPosition(_modelHandle[_selectCharacter[i].second], VGet(0, 0, 0));
		}
		else{
			// �v���C���[�������̏ꍇ�@���Ԋu
			float dis = 100.0f;
			float length = dis / (playerNum - 1);
		    MV1SetPosition(_modelHandle[_selectCharacter[i].second], VGet(-dis/2 + length * i, 0, 0));
		}
		// ���f���̕`��
		MV1DrawModel(_modelHandle[_selectCharacter[i].second]);
		printfDx("\n\nPlayer%d : %s",i+1,(_selectCharacter[i].first) ? "�I������" : "�I��");
	}
	return true;
};
