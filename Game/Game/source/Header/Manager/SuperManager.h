#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <utility>

class SuperManager 
{
	static SuperManager* _instance;
	public:
	SuperManager();
	~SuperManager();
	bool Init();
	bool AddManager(std::string name, int id,class ManagerBase* manager);
	bool Update();
	bool Draw();
	static SuperManager* GetInstance() {return _instance;}
	protected:
	std::vector<std::tuple<std::string,int,class ManagerBase*>> _superManager;
};

