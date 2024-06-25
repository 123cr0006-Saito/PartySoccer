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
	void Add(CollisionBase* collision);
	void Del(std::string name)override;
	void DelAll()override;

	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;

	virtual int GetListSize() override;

	bool CollisionCheckForCapsule(CollisionBase*);
	bool CollisionCheckForSphere(CollisionBase*);

protected:
	static CollisionManager* _instance;	
	std::vector<CollisionBase*> _addCollisionList;
	std::vector<CollisionBase*> _collisionList;
	std::vector<std::string> _delCollisionList;
};

