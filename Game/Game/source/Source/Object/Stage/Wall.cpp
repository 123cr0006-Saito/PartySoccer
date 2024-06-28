//----------------------------------------------------------------------
// @filename Wall.cpp
// @author: saito ko
// @explanation
// 壁クラス
//----------------------------------------------------------------------
#include "../../../Header/Object/Stage/Wall.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../AppFrame/MemoryLeak.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param オブジェクトの名前
// @param 位置
// @param 長さ
// @return 無し
//----------------------------------------------------------------------
Wall::Wall(const std::string& name, const Vector3D& pos, const Vector3D& length) : ObjectBase(name) {
	_obb = NEW OBB(name,pos,this);
	_obb->SetLength(length);
	SuperManager::GetInstance()->GetManager("collisionManager")->Add(_obb);
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Wall::~Wall(){
	SuperManager::GetInstance()->GetManager("collisionManager")->Delete(_obb);
};