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

	void Add(class UIBase*);
	void Del(std::string ui)override;
	void DelAll()override;
	void Sort();

	int GetListSize()override;
protected:
	std::vector<class UIBase*> _addUiList;
	std::vector<class UIBase*> _uiList;
	std::vector<std::string> _delUiList;
};