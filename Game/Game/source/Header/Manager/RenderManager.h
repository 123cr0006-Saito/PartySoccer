#pragma once
#include "ManagerBase.h"
class RenderManager : public ManagerBase
{
	static RenderManager* _instance;
public :
	RenderManager();
	~RenderManager();

	bool Init();
	void Add(std::string name ,int layer ,int model);
	void Del(std::string name);
	void DelAll();
	void Sort();

	static RenderManager* GetInstance() { return _instance; }
	std::string GetListName(std::string name)override;
	int GetListSize()override;
	bool Update();
	bool Draw();
	
protected:
	std::vector<std::tuple<std::string,int,int>> _modelList;
	std::vector<std::tuple<std::string, int, int>> _addModelList;
	std::vector<std::string> _delModelList;
};

