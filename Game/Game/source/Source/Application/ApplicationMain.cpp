#include "../../Header/Application/ApplicationMain.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Mode/ModeSelectPlayer.h"

// ŽÀ‘Ì
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }
	// ‰¹º‚Ì“Ç‚Ýž‚Ý
	global.SoundLoad();
	// ƒ‚[ƒh‚Ì“o˜^
	_superManager = NEW SuperManager();
	_renderManager = NEW RenderManager();
	_superManager->AddManager("renderManager", 0, _renderManager);
	ModeServer::GetInstance()->Add(NEW ModeGame(), 1, "ModeSelectPlayer");
	// FPS‚ðˆÀ’è‚³‚¹‚é‚½‚ß‚ÌƒNƒ‰ƒX‚ð‰Šú‰»
	_fpsController = NEW Fps();
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

