#include "../../../Header/Object/Stage/Stage.h"
#include "../../../Header/Manager/RenderManager.h"
Stage::Stage(std::string name) : ObjectBase(name) {
	_modelHandle = MV1LoadModel("Res/Model/Stage/Stadium.mv1");
	MV1SetPosition(_modelHandle, VGet(0, 0, 0));
	RenderManager::GetInstance()->Add(_name, 1, _modelHandle);
};

Stage::~Stage() {
	MV1DeleteModel(_modelHandle);
};

bool Stage::Init(){
	return true;
};

bool Stage::Update() {
	return true;
};