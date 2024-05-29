#pragma once
#include "ManagerBase.h"
#include "../Object/Base/ObjectBase.h"
class ObjectManager : public ManagerBase
{
	public:
	ObjectManager();
	~ObjectManager();
	bool Init() override;

	void Add(std::string name,ObjectBase* object);
	void Del(std::string name);
	void DelAll();
	void Sort();

	bool Update() override;
	bool Draw() override;

	std::string GetListName(std::string name)override;
	int GetListSize()override;
protected:
	std::vector<std::pair<std::string, ObjectBase*>> _objectList;
};

