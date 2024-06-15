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
	// マネージャーの取得
	_superManager = SuperManager::GetInstance();
	// オブジェクトの生成
	LoadObject();
	// カメラの生成
	_camera = NEW Camera();
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGame::LoadObject(){
	// オブジェクトの生成
	ObjectManager* objectManager = NEW ObjectManager();
	//ステージの生成
	objectManager->Add("Stage", NEW Stage("Stage"));
	//ボールの生成
	objectManager->Add("Ball", NEW Ball("Ball"));
	//ゴールの生成
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> goalList = LoadObjectParam("Data/GoalParam.csv");
	int count = 0;
	for (auto&& list : goalList) {
		std::string name = std::get<0>(list) + std::to_string(count + 1);
		Goal* goal = new Goal(name, std::get<1>(list), std::get<2>(list).Radian());
		objectManager->Add(name, goal);
		count++;
	}
	//ゴールネットコリジョンの生成
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> goalNetList = LoadObjectParam("Data/GoalNetParam.csv");
	for (auto&& list : goalNetList) {
		Wall* wall = NEW Wall();
		wall->SetName(std::get<0>(list));
		wall->SetColPos(std::get<1>(list));
		wall->SetColLength(std::get<2>(list));
		objectManager->Add(std::get<0>(list), wall);
	}
	//壁コリジョンの生成
	//std::vector<std::tuple<std::string, Vector3D, Vector3D>> wallList = LoadObjectParam("Data/WallParam.csv");
	//for (auto&& list : wallList) {
	//	Wall* wall = NEW Wall();
	//	wall->SetColPos(std::get<1>(list));
	//	wall->SetColLength(std::get<2>(list));
	//	objectManager->Add(std::get<0>(list), wall);
	//}
	

	// マネージャーに登録
	_superManager->AddManager("objectManager", 1, objectManager);
	return true;
};

std::vector<std::tuple<std::string, Vector3D, Vector3D>> ModeGame::LoadObjectParam(std::string fileName) {
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> nameList;
	// csvファイルを読み込む
	CFile file(fileName);
	// ファイルが開けた場合
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string name;
			Vector3D pos,param;
			c += GetString(&p[c],&name); // 名前を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.x); //x座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.y); //y座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.z); //z座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.x); //xの長さを取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.y); //yの長さを取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &param.z); //zの長さを取得
			c += SkipSpace(&p[c], &p[size]); // 空白やコントロールコードをスキップする
			nameList.push_back(std::make_tuple(name,pos,param));
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
