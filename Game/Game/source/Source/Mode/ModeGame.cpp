#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Object/Stage/Stage.h"
#include "../../Header/Object/Stage/Ball.h"
#include "../../Header/Object/Stage/Goal.h"
#include "../../Header/Object/Stage/Wall.h"
#include "../../Header/Manager/RenderManager.h"
#include "../../Header/Manager/CollisionManager.h"
#include "../AppFrame/source/CFile/CFile.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	_superManager = SuperManager::GetInstance();
	SetupCamera_Perspective(60.0f * 180.0f / 3.141592f);
	ObjectManager* objectManager = NEW ObjectManager();
	Vector3D goalPos[2] = { Vector3D(6300, 0, 800), Vector3D(-6300, 0, 800) };
	Vector3D goalRot[2] = { Vector3D(0, 180 * 3.141592f / 180.0f, 0), Vector3D(0, 0, 0) };
	for (int i = 0; i < 2; i++) {
		std::string name = "Goal_" + std::to_string(i + 1);
		Goal* goal = new Goal(name, goalPos[i], goalRot[i]);
		objectManager->Add(name,goal);
	}
	objectManager->Add("Stage", NEW Stage("Stage"));
	objectManager->Add("Ball", NEW Ball("Ball"));

	_superManager->AddManager("objectManager",1, objectManager);
	_camera = NEW Camera();

	std::vector<std::tuple<Vector3D, Vector3D, Vector3D>> wallList = WallLoad();
	for(auto&& list : wallList){
		Wall* wall = NEW Wall();
		wall->SetColPos(std::get<0>(list));
		wall->SetColLength(std::get<1>(list));
		wall->SetForwardVec(std::get<2>(list));
		objectManager->Add("wall", wall);
	}
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

std::vector<std::tuple<Vector3D, Vector3D, Vector3D>> ModeGame::WallLoad() {
	std::vector<std::tuple<Vector3D, Vector3D, Vector3D>> nameList;
	std::string filePath = "Data/WallParam.csv";
	// csvファイルを読み込む
	CFile file(filePath);
	// ファイルが開けた場合
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			int x, y, z, lengthX, lengthY, lengthZ,normX,normY,normZ;
			c += GetDecNum(&p[c], &x); // obbのXサイズを取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &y); // obbのYサイズを取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &z); // obbのZサイズを取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &lengthX);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &lengthY);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &lengthZ);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &normX);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &normY);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &normZ);
			c += SkipSpace(&p[c], &p[size]); // 空白やコントロールコードをスキップする
			nameList.push_back(std::make_tuple(Vector3D(x, y, z), Vector3D(lengthX, lengthY, lengthZ),Vector3D(normX, normY, normZ)));
		}
	}
	else {
		DebugErrar();
	}
	return nameList;
};


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
