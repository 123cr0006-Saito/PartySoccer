#pragma once
#include "ManagerBase.h"
class UIManager : public ManagerBase
{ 
	public:
	UIManager();
	virtual ~UIManager();
	bool Init()override;
	bool Update()override;
	bool Draw()override;

	void Add(std::tuple<std::string, int, class UIBase*> ui);
	void Del(std::string ui)override;
	void DelAll();
	void Sort();

	int GetListSize()override;
protected:
	std::vector<std::tuple<std::string, int,class UIBase*>> _addUiList;
	std::vector<std::tuple<std::string, int, class UIBase*>> _uiList;
	std::vector<std::string> _delUiList;
};