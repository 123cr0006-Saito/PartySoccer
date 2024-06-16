#pragma once
#include "ManagerBase.h"
class RenderManager : public ManagerBase
{
public :
	RenderManager();
	~RenderManager();

	bool Init();
	void Add(std::string name ,int layer ,int model);
	void Del(std::string name)override;
	void DelAll();
	void Sort();

	int GetListSize()override;
	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;
	
protected:
	std::vector<std::tuple<std::string,int,int>> _modelList;
	std::vector<std::tuple<std::string, int, int>> _addModelList;
	std::vector<std::string> _delModelList;
};

