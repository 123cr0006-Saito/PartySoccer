#pragma once
#include "ManagerBase.h"
class SuperManager 
{
	static SuperManager* _instance;
	public:
	SuperManager();
	~SuperManager();
	bool Init();
	bool AddManager(int id, ManagerBase* manager);
	bool Update();
	bool Draw();
	static SuperManager* GetInstance() {return _instance;}
	protected:
	std::vector<std::pair<int,ManagerBase*>> _superManager;
};

