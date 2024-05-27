#include "../../../Header/Object/Stage/Goal.h"

Goal::Goal(std::string name, Vector3D pos) : ObjectBase(name) {
	MV1SetPosition(_modelHandle, pos.toVECTOR());
};

Goal::~Goal(){

};

bool Goal::Init(){
	return true;
};

bool Goal::Update() {
	return true;
};