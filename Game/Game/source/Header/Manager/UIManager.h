#pragma once
#include "ManagerBase.h"
class UIManager : public ManagerBase
{ 
	public:
	UIManager();
	virtual ~UIManager();
	virtual bool Terminate()override;
	bool Init()override;
	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;

	void Add(class UIBase*);
	void AddInput(void* value)override;
	void DeleteName(std::string ui)override;
	void DeleteInput(void* value)override;
	void DelAll()override;
	void Sort();

	int GetListSize()override;
protected:
	std::vector<class UIBase*> _addUiList;
	std::vector<class UIBase*> _uiList;
	std::vector<class UIBase*> _delUiList;
	std::vector<std::string> _delUiNameList;
};