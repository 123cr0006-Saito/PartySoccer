#include "../../../Header/Object/Stage/Stage.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/SuperManager.h"
Stage::Stage(std::string name) : ObjectBase(name) {
	_modelHandle = MV1LoadModel("Res/Model/Stage/Stadium.mv1");
	MV1SetPosition(_modelHandle, VGet(0, 0, 0));
	RenderManager* renderManager = dynamic_cast<RenderManager*>(SuperManager::GetInstance()->GetManager("renderManager"));
	renderManager->Add(_name, 1, _modelHandle);

	for(int i = 0; i < 3; i++){
		MV1SetFrameVisible(_modelHandle,351+i,false);// 使用しないフレームの番号を指定　非表示に設定
	}
	
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