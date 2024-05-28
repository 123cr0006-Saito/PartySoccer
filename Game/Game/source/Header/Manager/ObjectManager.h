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

	bool AddObject(int id, ObjectBase* object);
	std::string GetListName(std::string name)override;
	int GetListSize()override;
};

