#pragma once
#include "ManagerBase.h"
class RenderManager : public ManagerBase
{
public :
	RenderManager();
	~RenderManager();

	bool Init();
	void Add(int layer , class ModelBase* model);
	void Del(std::string name)override;
	void DelAll()override;
	void Sort();

	int GetListSize()override;
	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;
	
protected:
	std::vector<std::pair<int,class ModelBase*>> _modelList;
	std::vector<std::pair<int, class ModelBase*>> _addModelList;
	std::vector<std::string> _delModelList;
};

