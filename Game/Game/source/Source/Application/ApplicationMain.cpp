#include "../../Header/Application/ApplicationMain.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Mode/ModeSelectPlayer.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/RenderManager.h"
#include "../../Header/Manager/CollisionManager.h"
#include "../../Header/Manager/UIManager.h"
// ����
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }
	// �����̓ǂݍ���
	global.SoundLoad();
	
	// �O�̏������獡�̏����̌v�Z���Ԃ𓾂�N���X
	_timer = NEW Timer();
	_timer->Start();
	// FPS�����肳���邽�߂̃N���X��������
	_fpsController = NEW Fps();

	// ���[�h�̓o�^
	SuperManager* superManager = NEW SuperManager();
	RenderManager* renderManager = NEW RenderManager();
	CollisionManager* collisionManager = NEW CollisionManager();
	UIManager* uiManager = NEW UIManager();
	superManager->AddManager("renderManager", 100, renderManager);
	superManager->AddManager("collisionManager", 0, collisionManager);
	superManager->AddManager("uiManager", 1000, uiManager);
	ModeServer::GetInstance()->Add(NEW ModeSelectPlayer(), 1, "ModeSelectPlayer");
	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	delete _fpsController;
	ResourceServer::DeleteResourceAll();
	return true;
}

bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	_fpsController->WaitFps();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	_fpsController->DrawFps(0,0);
	return true;
}

