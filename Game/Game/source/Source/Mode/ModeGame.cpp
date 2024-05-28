
#include "../../Header/Mode/ModeGame.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	_superManager = SuperManager::GetInstance();
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGame::Process() {
	base::Process();
	_superManager->Update();
	return true;
}

bool ModeGame::Render() {
	base::Render();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	_superManager->Draw();
	return true;
}
