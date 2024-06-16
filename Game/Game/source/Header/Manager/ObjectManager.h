#pragma once
#include "ManagerBase.h"
class ObjectManager : public ManagerBase
{
	public:
	ObjectManager();
	~ObjectManager();
	bool Init() override;

	void Add(std::string name,class ObjectBase* object);
	void Del(std::string name)override;
	void DelAll();
	void Sort();

	bool Update()override;
	bool UpdateEnd()override;
	bool Draw() override;

	class ObjectBase* Get(std::string name);
	int GetListSize()override;
protected:
	std::vector<std::pair<std::string, class ObjectBase*>> _objectList;
};

