#include "../../../Header/Object/Stage/Stage.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../AppFrame/source/System/Header/Resource/ResourceServer.h"
#include "../../../Header/Model/Base/ModelBase.h"
#include "../AppFrame/MemoryLeak.h"
Stage::Stage(std::string name) : ObjectBase(name) {
	int handle = ResourceServer::MV1LoadModel("Stage","Res/Model/Stage/Stadium.mv1");
	for (int i = 0; i < 3; i++) {
		MV1SetFrameVisible(handle, 351 + i, false);// 使用しないフレームの番号を指定　非表示に設定
	}

	_model = NEW ModelBase(name, 1,handle);
	_model->SetPos(_pos);
	RenderManager* renderManager = dynamic_cast<RenderManager*>(SuperManager::GetInstance()->GetManager("renderManager"));
	renderManager->Add(_model);
};

Stage::~Stage() {
	
};

bool Stage::Init(){
	return true;
};

bool Stage::Update() {
	return true;
};