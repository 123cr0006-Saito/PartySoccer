#include "../../Header/Mode/ModeResult.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/PlayerManager.h"
#include "../../Header/Object/Player/Player.h"
#include "../../Header/Mode/ModeTitle.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../../Header/Other/Score.h"
#include "../../Header/Other/Camera/Camera.h"
#include "../AppFrame/MemoryLeak.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../../Header/UI/Animation/LocationAnim.h"
#include "../../Header/Manager/UIManager.h"

ModeResult::ModeResult(){

};

ModeResult::~ModeResult(){

};

bool	ModeResult::Initialize(){
	_superManager = SuperManager::GetInstance();
	_playerManager = dynamic_cast<PlayerManager*>(_superManager->GetManager("playerManager"));
	_score = Score::GetInstance();
	_camera = Camera::GetInstance();
	_input = NEW XInput(PLAYER_1);
	_currentTime = GetNowCount();
	// ���҂��擾
	_winnerTeam = _score->GetWinner();
	// �v���C���[�̃��X�g���擾
	std::vector<Player*> player = _playerManager->GetList();
	int playerNum = player.size();
	// �v���C���[�̈ʒu��ݒ�
	for (int i = 0; i < playerNum; i++) {
		if (playerNum == 1) {
			// �v���C���[����l�̏ꍇ�@���S
			player[i]->SetPos(Vector3D(0, 0, 0));
			player[i]->SetForwardVec(Vector3D(0, 0, -1));
			//player[i]->SetIsGame(false);
		}
		else {
		// �v���C���[�������̏ꍇ�@���Ԋu
			float dis = 1500.0f;
			float length = dis / (playerNum - 1);
			player[i]->SetPos(Vector3D(-dis / 2 + length * i, 0, 0));
		}
	}

	int handle,x,y;
	handle = LoadGraph(("Res/UI/WinFrame" + _winnerTeam + ".png").c_str());
	GetGraphSize(handle, &x, &y);
	UIRotaBase* ui = NEW UIRotaBase("WinTeam",Vector3D(1920 / 2, -500, 0), Vector3D(x / 2, y / 2, 0), Vector3D(1.0f, 1.0f, 0.0f), 0, 255, handle, 100);
	LocationAnim* anim = NEW LocationAnim(ui, "Data/UIAnimation/WinTeamAnimation.csv");
	ui->SetAnimation(anim);
	dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"))->Add(ui);
	global._soundServer->DirectPlay("BGM_Cheers");
	return true;
};


bool	ModeResult::Terminate(){
	_superManager->DeleteName("playerManager");
	_superManager->GetManager("objectManager")->DelAll();
	_superManager->GetManager("uiManager")->DelAll();
	delete _camera;
	delete _score;
	delete _input;
	return true;
};

bool	ModeResult::Process(){
	int nowTime = GetNowCount() - _currentTime;
	_input->Input();
	_camera->Update();
	SetCameraPositionAndTarget_UpVecY(VGet(0, 800, -2000), VGet(0, 0, 0));
	ModeServer* modeServer = ModeServer::GetInstance();
	// 5�b���A�{�^���Ń^�C�g���ɖ߂�
	// �^�C�g���ɖ߂�
	if(nowTime > 5000 &&_input->GetTrg(XINPUT_BUTTON_A) && !modeServer->Search("ModeTitle")){
		// ���[�h��ύX
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 0, "ModeTitle");
		std::vector<std::string> modeName = {"ModeResult"};
		ModeServer::GetInstance()->Add(NEW ModeFadeComeBack(100, modeName, "ModeTitle",1, true),10,"ModeFadeComeBack");
		ModeServer::GetInstance()->Del(this);
	}
	return true;
};

bool	ModeResult::Render(){
	return true;
};
