#pragma once
#include "ManagerBase.h"
class ObjectManager : public ManagerBase
{
	public:
	ObjectManager();
	~ObjectManager();
	virtual bool Terminate()override;
	bool Init() override;

	void Add(class ObjectBase* object);
	void AddInput(void* value)override;
	void DeleteName(std::string name)override;
	void DeleteInput(void* value)override;
	void DelAll()override;

	bool Update()override;
	bool UpdateEnd()override;
	bool Draw() override;

	class ObjectBase* Get(std::string name);
	int GetListSize()override;
protected:
	std::vector<class ObjectBase*> _addObjectList;
	std::vector<class ObjectBase*> _objectList;
	std::vector<class ObjectBase*> _delObjectList;
	std::vector<std::string> _delObjectNameList;
};

