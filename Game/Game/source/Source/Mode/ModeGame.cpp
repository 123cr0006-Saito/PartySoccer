#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Object/Stage/Stage.h"
#include "../../Header/Object/Stage/Ball.h"
#include "../../Header/Object/Stage/Goal.h"
#include "../../Header/Manager/RenderManager.h"


bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	_superManager = SuperManager::GetInstance();
	SetupCamera_Perspective(60.0f * 180.0f / 3.141592f);
	ObjectManager* objectManager = NEW ObjectManager();
	Vector3D goalPos[2] = { Vector3D(0, 0, 0), Vector3D(0, 0, 0) };
	Vector3D goalRot[2] = { Vector3D(0, 90, 0), Vector3D(0, -90, 0) };
	//for (int i = 0; i < 2; i++) {
	//	std::string name = "Goal_" + std::to_string(i + 1);
	//	Goal* goal = new Goal(name, goalPos[i], goalRot[i]);
	//	objectManager->Add(name,goal);
	//}
	objectManager->Add("Stage", NEW Stage("Stage"));
	objectManager->Add("Ball", NEW Ball("Ball"));

	_superManager->AddManager("objectManager",1, objectManager);
	_camera = NEW Camera();
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGame::Process() {
	base::Process();
	_superManager->Update();
	_camera->Update();
	return true;
}

bool ModeGame::Render() {
	base::Render();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	_superManager->Draw();
	_camera->Draw();
	return true;
}
