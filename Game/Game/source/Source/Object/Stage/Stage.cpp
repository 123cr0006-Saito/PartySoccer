//----------------------------------------------------------------------
// @filename Stage.cpp
// @author: saito ko
// @explanation
// オブジェクトを管理するクラス
//----------------------------------------------------------------------
#include "../../../Header/Object/Stage/Stage.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../AppFrame/source/System/Header/Resource/ResourceServer.h"
#include "../../../Header/Model/Base/ModelBase.h"
#include "../AppFrame/MemoryLeak.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param オブジェクトの名前
// @return 無し
//----------------------------------------------------------------------
Stage::Stage(std::string name) : ObjectBase(name) {
	int handle = ResourceServer::MV1LoadModel("Stage","Res/Model/Stage/Stadium.mv1");
	for (int i = 0; i < 3; i++) {
		MV1SetFrameVisible(handle, 351 + i, false);// 使用しないフレームの番号を指定　非表示に設定
	}

	_model = NEW ModelBase(name, 1,handle);
	_model->SetPos(_pos);
	SuperManager::GetInstance()->GetManager("renderManager")->Add(_model);
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Stage::~Stage() {
	SuperManager::GetInstance()->GetManager("renderManager")->Delete(_model);
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Stage::Update() {
	return true;
};