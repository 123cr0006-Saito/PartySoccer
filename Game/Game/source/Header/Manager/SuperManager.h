#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <utility>

class SuperManager 
{
public:
	SuperManager();
	~SuperManager();
	bool Init();
	bool AddManager(std::string name, int id,class ManagerBase* manager);
	class ManagerBase* GetManager(std::string name);
	bool Update();
	bool Draw();

	void Sort();
	static SuperManager* GetInstance() { return _instance;}
	void Skip() { _isProcessSkip = true; }
protected:
	static SuperManager* _instance;
	bool _isSort;
	std::vector<std::tuple<std::string,int,class ManagerBase*>> _superManager;
	bool _isProcessSkip;
};

