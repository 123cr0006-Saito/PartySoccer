#include "../../Header/Application/ApplicationMain.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Mode/ModeSelectPlayer.h"

// 実体
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }
	// 音声の読み込み
	global.SoundLoad();
	// モードの登録
	_superManager = NEW SuperManager();
	_renderManager = NEW RenderManager();
	ModeServer::GetInstance()->Add(NEW ModeSelectPlayer(), 1, "ModeSelectPlayer");

	// コントローラーの初期化
	//_input = NEW XInput(DX_INPUT_PAD1);
	// FPSを安定させるためのクラスを初期化
	_fpsController = NEW Fps();
	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	delete _input;
	delete _fpsController;
	ResourceServer::DeleteResourceAll();
	return true;
}

bool ApplicationMain::Input() {
	base::Input();
	
	_input->Input();
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

