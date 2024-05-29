#include "../../../Header/Object/Stage/Goal.h"
#include "../../../Header/Manager/RenderManager.h"
Goal::Goal(std::string name, Vector3D pos, Vector3D rotation) : ObjectBase(name) {
	MV1SetPosition(_modelHandle, pos.toVECTOR());
	MV1SetRotationXYZ(_modelHandle, pos.toVECTOR());
	RenderManager::GetInstance()->Add(_name,1,_modelHandle);
};

Goal::~Goal(){
	MV1DeleteModel(_modelHandle);
};

};

bool Goal::Init(){
	return true;
};

bool Goal::Update() {
	return true;
};