#include "../../Header/Application/ApplicationMain.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Mode/ModeSelectPlayer.h"
#include "../../Header/Mode/ModeTitle.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/RenderManager.h"
#include "../../Header/Manager/CollisionManager.h"
#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Manager/UIManager.h"
// ����
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }
	// �����̓ǂݍ���
	//global.SoundLoad();
	
	// �O�̏������獡�̏����̌v�Z���Ԃ𓾂�N���X
	_timer = NEW Timer();
	_timer->Start();
	// FPS�����肳���邽�߂̃N���X��������
	_fpsController = NEW Fps();

	// ���[�h�̓o�^
	_superManager = NEW SuperManager();
	RenderManager* renderManager = NEW RenderManager();
	CollisionManager* collisionManager = NEW CollisionManager();
	ObjectManager* objectManager = NEW ObjectManager();
	UIManager* uiManager = NEW UIManager();
	_superManager->Add("renderManager", 100, renderManager);
	_superManager->Add("collisionManager", 0, collisionManager);
	_superManager->Add("objectManager", 1, objectManager);
	_superManager->Add("uiManager", 1000, uiManager);

	ModeServer::GetInstance()->Add(NEW ModeTitle(), 1, "ModeTitle");
	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	delete _timer;
	delete _fpsController;
	delete _superManager;
	ResourceServer::DeleteResourceAll();
	return true;
}

bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	_superManager->Update();
	_fpsController->WaitFps();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	_superManager->Draw();
	_fpsController->DrawFps(0,0);
	return true;
}

