#include "../../../Header/Object/Stage/Wall.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../AppFrame/MemoryLeak.h"

Wall::Wall(std::string name, Vector3D pos, Vector3D length) : ObjectBase(name) {
	_obb = NEW OBB(name,pos,this);
	_obb->SetLength(length);
	SuperManager::GetInstance()->GetManager("collisionManager")->Add(_obb);
};

Wall::~Wall(){
	SuperManager::GetInstance()->GetManager("collisionManager")->Delete(_obb);
};