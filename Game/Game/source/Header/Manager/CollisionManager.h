#pragma once
#include "ManagerBase.h"
#include "../Object/Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
class CollisionManager:public ManagerBase
{
public:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* GetInstance(){return _instance;};
	void Add(ObjectBase* object, CollisionBase* collision);
	void Del(std::string name);
	bool Update();

	virtual std::string GetListName(std::string name)override;
	virtual int GetListSize() override;

	bool CollisionCheckForCapsule(std::pair<ObjectBase*, CollisionBase*>&);
	bool CollisionCheckForSphere(std::pair<ObjectBase*, CollisionBase*>&);

protected:
	static CollisionManager* _instance;	
	std::vector<std::pair<ObjectBase*, CollisionBase*>> _addCollisionList;
	std::vector<std::pair<ObjectBase*,CollisionBase*>> _collisionList;
	std::vector<std::string> _delCollisionList;
};
