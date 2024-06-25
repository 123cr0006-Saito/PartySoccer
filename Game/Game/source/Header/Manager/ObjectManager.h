#pragma once
#include "ManagerBase.h"
class ObjectManager : public ManagerBase
{
	public:
	ObjectManager();
	~ObjectManager();
	bool Init() override;

	void Add(class ObjectBase* object);
	void Del(std::string name)override;
	void DelAll()override;

	bool Update()override;
	bool UpdateEnd()override;
	bool Draw() override;

	class ObjectBase* Get(std::string name);
	int GetListSize()override;
protected:
	std::vector<class ObjectBase*> _addObjectList;
	std::vector<class ObjectBase*> _objectList;
	std::vector<std::string> _delObjectList;
};

