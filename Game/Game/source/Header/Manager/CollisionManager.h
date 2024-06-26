#pragma once
#include "ManagerBase.h"
#include "../Object/Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
class CollisionManager:public ManagerBase
{
public:
	CollisionManager();
	~CollisionManager();
	virtual bool Terminate()override;
	void Add(CollisionBase* collision);
	void AddInput(void* value)override;
	void DeleteName(std::string name)override;
	void DeleteInput(void* value)override;
	void DelAll()override;

	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;

	virtual int GetListSize() override;

	bool CollisionCheckForCapsule(CollisionBase*);
	bool CollisionCheckForSphere(CollisionBase*);

protected:
	std::vector<CollisionBase*> _addCollisionList;
	std::vector<CollisionBase*> _collisionList;
	std::vector<CollisionBase*> _delCollisionList;
	std::vector<std::string> _delCollisionNameList;
};

