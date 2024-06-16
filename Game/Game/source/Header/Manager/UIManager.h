#pragma once
#include "ManagerBase.h"
class UIManager : public ManagerBase
{ 
	public:
	UIManager();
	virtual ~UIManager();
	bool Init()override;
	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;

	void Add(std::string, int, class UIBase*);
	void Del(std::string ui)override;
	void DelAll();
	void Sort();

	std::vector<std::tuple<std::string, int, class UIBase*>>* GetUiList();
	int GetListSize()override;
protected:
	std::vector<std::tuple<std::string, int,class UIBase*>> _addUiList;
	std::vector<std::tuple<std::string, int, class UIBase*>> _uiList;
	std::vector<std::string> _delUiList;
};