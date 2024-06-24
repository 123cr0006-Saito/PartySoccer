#include "../../../Header/Object/Stage/Goal.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../AppFrame/source/System/Header/Resource/ResourceServer.h"
#include "../../../Header/Model/Base/ModelBase.h"
Goal::Goal(std::string name, Vector3D pos, Vector3D rotation) : ObjectBase(name) {
	int handle = ResourceServer::MV1LoadModel("Goal","Res/Model/Goal/goal.mv1");
	_model = NEW ModelBase(name, handle);
	_model->SetPos(pos);
	_model->SetRotation(rotation);
	_model->SetScale(Vector3D(5, 5, 5));

	RenderManager* renderManager = dynamic_cast<RenderManager*>(SuperManager::GetInstance()->GetManager("renderManager"));
	renderManager->Add(1, _model);

	_obb = NEW OBB();
	_obb->SetName("goal");
	_obb->pos = pos + Vector3D(-300*cos(rotation.y), 0, 0);
	_obb->Rotate(rotation);
	_obb->SetLength(Vector3D(600, 1800, 2500));
	CollisionManager::GetInstance()->Add(this, _obb);
};

Goal::~Goal(){
	
};


bool Goal::Init(){
	return true;
};

bool Goal::Update() {
	return true;
};

bool Goal::DebugDraw() {
	return true;
}