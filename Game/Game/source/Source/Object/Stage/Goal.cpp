//----------------------------------------------------------------------
// @filename Goal.cpp
// @author: saito ko
// @explanation
// ゴールクラス
//----------------------------------------------------------------------
#include "../../../Header/Object/Stage/Goal.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../AppFrame/source/System/Header/Resource/ResourceServer.h"
#include "../../../Header/Model/Base/ModelBase.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param オブジェクトの名前
// @param オブジェクトの位置
// @param オブジェクトの回転値
// @return 無し
//----------------------------------------------------------------------
Goal::Goal(const std::string& name, const Vector3D& pos, const Vector3D& rotation) : ObjectBase(name) {
	int handle = ResourceServer::MV1LoadModel("Goal","Res/Model/Goal/goal.mv1");
	_model = NEW ModelBase(name, 1, handle);
	_model->SetPos(pos);
	_model->SetRotation(rotation);
	_model->SetScale(Vector3D(5, 5, 5));

	SuperManager::GetInstance()->GetManager("renderManager")->Add(_model);
	_obb = NEW OBB("goal", pos + Vector3D(-300 * cos(rotation.y), 0, 0), Vector3D(600, 1800, 2500), this);
	SuperManager::GetInstance()->GetManager("collisionManager")->Add(_obb);
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Goal::~Goal(){
	SuperManager::GetInstance()->GetManager("collisionManager")->Delete(_obb);
	SuperManager::GetInstance()->GetManager("renderManager")->Delete(_model);
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Goal::Update() {
	return true;
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Goal::DebugDraw() {
	return true;
}