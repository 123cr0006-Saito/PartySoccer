#include "../../../Header/Object/Stage/Goal.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../AppFrame/MemoryLeak.h"
Goal::Goal(std::string name, Vector3D pos, Vector3D rotation) : ObjectBase(name) {
	_modelHandle = MV1LoadModel("Res/Model/Goal/goal.mv1");
	MV1SetPosition(_modelHandle, pos.toVECTOR());
	MV1SetRotationXYZ(_modelHandle, rotation.toVECTOR());
	MV1SetScale(_modelHandle, (Vector3D(1.0f, 1.0f, 1.0f) * 5).toVECTOR());

	RenderManager* renderManager = dynamic_cast<RenderManager*>(SuperManager::GetInstance()->GetManager("renderManager"));
	renderManager->Add(_name, 1, _modelHandle);

	_obb = NEW OBB();
	_obb->SetName("goal");
	_obb->pos = pos;
	_obb->Rotate(rotation);
	_obb->SetLength(Vector3D(1300, 1800, 2500));
	CollisionManager::GetInstance()->Add(this, _obb);
};

Goal::~Goal(){
	MV1DeleteModel(_modelHandle);
	delete _obb;
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