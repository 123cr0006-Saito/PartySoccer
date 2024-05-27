#include "../../../Header/Object/Stage/Stage.h"

Stage::Stage(std::string name) : ObjectBase(name) {
	_modelHandle = MV1LoadModel("Res/Model/Stage/stage.mv1");
	MV1SetPosition(_modelHandle, VGet(0, 0, 0));
};

Stage::~Stage() {

};

bool Stage::Init(){
	return true;
};

bool Stage::Update() {
	return true;
};