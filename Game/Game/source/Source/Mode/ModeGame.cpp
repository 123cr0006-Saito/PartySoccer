#include "../AppFrame/source/CFile/CFile.h"

#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Mode/ModeGameEnd.h"

#include "../../Header/Object/Player/Player.h"
#include "../../Header/Object/Stage/Stage.h"
#include "../../Header/Object/Stage/Ball.h"
#include "../../Header/Object/Stage/Goal.h"
#include "../../Header/Object/Stage/Wall.h"

#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/RenderManager.h"
#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Manager/RenderManager.h"
#include "../../Header/Manager/CollisionManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Manager/PlayerManager.h"

#include "../../Header/Other/Score.h"
#include "../../Header/Other/Camera/Camera.h"
#include "../../Header/Other/TimeLimit.h"

#include "../../Header/UI/Score/UIScoreBoard.h"
#include "../../Header/UI/UIStartCount.h"
#include "../../Header/UI/UITimer.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	// マネージャーの取得
	_superManager = SuperManager::GetInstance();
	ChangeLightTypeDir(VGet(0,0,1));
	// オブジェクトの生成
	LoadObject();
	// カメラの生成
	_camera = Camera::GetInstance();
	_camera->SetIsGame(true);
	_score = NEW Score();
	_timeLimit = NEW TimeLimit();
	_timeLimit->SetTimeLimit(0, 5);
	_timeLimit->Stop();

	Vector3D pos[2] = { Vector3D(600,100,0),Vector3D(1300,100,0) };
	for(int i = 0; i < 2; i++){
		UIScoreBoard* uiScore = NEW UIScoreBoard(pos[i], "Goal_" + std::to_string(i+1), _score);
	}
	UIStartCount* uiStartCount = NEW UIStartCount();
	UITimer* uiTimer = NEW UITimer(_timeLimit);

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	// オブジェクトの削除
	ObjectManager* objectManager = dynamic_cast<ObjectManager*>(_superManager->GetManager("objectManager"));
	for(auto&& list : _objectName){
		objectManager->Del(list);
	}
	// モデルの削除
	RenderManager* renderManager = dynamic_cast<RenderManager*>(_superManager->GetManager("renderManager"));
	for (auto&& list : _objectName) {
		renderManager->Del(list);
	}
	// UIの削除
	UIManager* uiManager = dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"));
	PlayerManager* playerManager = dynamic_cast<PlayerManager*>(_superManager->GetManager("playerManager"));
	std::vector<std::pair<std::string, Player*>> player = playerManager->GetList();
	for(auto&& list : player){
		uiManager->Del(list.second->GetName() + "Frame");
	}
	uiManager->Del("scoreBoard"); 
	uiManager->Del("scoreNum");
	uiManager->Del("Time");

	_superManager->GetManager("collisionManager")->DelAll();

	_camera->SetIsGame(false);
	_camera->SetPos(Vector3D(0, 800, -2000));
	_camera->SetTarget(Vector3D(0, 0, 0));

	delete _timeLimit;
	return true;
}

void ModeGame::ReSetGame(){
	// ボールの位置を設定
	ObjectManager* objectManager = dynamic_cast<ObjectManager*>(_superManager->GetManager("objectManager"));
	Ball* ball = dynamic_cast<Ball*>(objectManager->Get("Ball"));
	ball->SetPos(Vector3D(0, 350, 0));
	ball->SetSpeed(0);
	PlayerManager* playerManager = dynamic_cast<PlayerManager*>(_superManager->GetManager("playerManager"));
	playerManager->InitParam();
	UIStartCount* uiStartCount = NEW UIStartCount();
};

bool ModeGame::LoadObject(){
	ObjectManager* objectManager = dynamic_cast<ObjectManager*>(_superManager->GetManager("objectManager"));
	//ボールの生成
	objectManager->Add("Ball", NEW Ball("Ball"));
	_objectName.push_back("Ball");
	//ゴールの生成
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> goalList = LoadObjectParam("Data/GoalParam.csv");
	int count = 1;
	for (auto&& list : goalList) {
		std::string name = std::get<0>(list) + std::to_string(count);
		Goal* goal = new Goal(name, std::get<1>(list), std::get<2>(list).Radian());
		objectManager->Add(name, goal);
		_objectName.push_back(name);
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
		_objectName.push_back(std::get<0>(list));
	}
	//壁コリジョンの生成
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> wallList = LoadObjectParam("Data/WallParam.csv");
	for (auto&& list : wallList) {
		Wall* wall = NEW Wall();
		wall->SetColPos(std::get<1>(list));
		wall->SetColLength(std::get<2>(list));
		objectManager->Add(std::get<0>(list), wall);
		_objectName.push_back(std::get<0>(list));
	}

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
	_camera->Update();
	_timeLimit->Update();

	ModeServer* modeServer = ModeServer::GetInstance();
	if (!modeServer->Search("ModeGameEnd") && _timeLimit->GetTimeLimit() <= 0) {
		ModeServer::GetInstance()->Add(NEW ModeGameEnd(),10,"ModeGameEnd");
	}

	return true;
}

bool ModeGame::Render() {
	base::Render();
	_camera->Draw();
	return true;
}
