#pragma once
#include "ManagerBase.h"
#include "../Object/Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
class CollisionManager:public ManagerBase
{
public:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* GetInstance();
	void Add(ObjectBase* object, CollisionBase* collision);
	bool Update();

	bool CollisionCheckForCapsule(std::pair<ObjectBase*, CollisionBase*>);
	bool CollisionCheckForSphere(std::pair<ObjectBase*, CollisionBase*>);

protected:
	static CollisionManager* _instance;	
	std::vector<std::pair<ObjectBase*,CollisionBase*>> _collisionList;
};

