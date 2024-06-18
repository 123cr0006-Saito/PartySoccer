#include "../../../Header/Object/Stage/Wall.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../AppFrame/MemoryLeak.h"

Wall::Wall() : ObjectBase("wall") {
	_obb = NEW OBB();
	_obb->SetName("wall");
	CollisionManager::GetInstance()->Add(this, _obb);
};

Wall::~Wall(){
	
};