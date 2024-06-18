#include "../../Header/Mode/ModeResult.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/PlayerManager.h"
#include "../../Header/Mode/ModeTitle.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../../Header/Other/Score.h"
#include "../AppFrame/MemoryLeak.h"

ModeResult::ModeResult(){

};

ModeResult::~ModeResult(){

};

bool	ModeResult::Initialize(){
	_superManager = SuperManager::GetInstance();
	_playerManager = dynamic_cast<PlayerManager*>(_superManager->GetManager("playerManager"));
	_score = Score::GetInstance();
	_input = NEW XInput(PLAYER_1);
	// ���҂��擾
	_winnerTeam = _score->GetWinner();
	// �v���C���[�̃��X�g���擾
	std::vector<std::pair<std::string, Player*>> player = _playerManager->GetList();
	int playerNum = player.size();
	// �v���C���[�̈ʒu��ݒ�
	for (int i = 0; i < playerNum; i++) {
		if (playerNum == 1) {
			// �v���C���[����l�̏ꍇ�@���S
			player[i].second->SetPos(Vector3D(0, 0, 0));
		}
		else {
		// �v���C���[�������̏ꍇ�@���Ԋu
			float dis = 100.0f;
			float length = dis / (playerNum - 1);
			player[i].second->SetPos(Vector3D(-dis / 2 + length * i, 0, 0));
			player[i].second->SetScale(Vector3D(1,1,1));
		}
	}

	// �J�����̐ݒ�
	SetupCamera_Ortho(100);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -100), VGet(0, 0, 0));

	return true;
};

bool	ModeResult::Terminate(){
	_superManager->Del("playerManager");
	_superManager->GetManager("collisionManager")->DelAll();
	_superManager->GetManager("renderManager")->DelAll();
	_superManager->GetManager("uiManager")->DelAll();
	delete _score;
	delete _input;
	return true;
};

bool	ModeResult::Process(){
	_input->Input();
	ModeServer* modeServer = ModeServer::GetInstance();
	if(_input->GetTrg(XINPUT_BUTTON_A) && !modeServer->Search("ModeTitle")){
		// ���[�h��ύX
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 0, "ModeTitle");
		std::vector<std::string> modeName = {"ModeResult"};
		ModeServer::GetInstance()->Add(NEW ModeFadeComeBack(1000, modeName, "ModeTitle",1, true),10,"ModeFadeComeBack");
		ModeServer::GetInstance()->Del(this);
	}
	return true;
};

bool	ModeResult::Render(){
	return true;
};
