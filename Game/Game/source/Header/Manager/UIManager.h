//----------------------------------------------------------------------
// @filename UIManager.h
// @author: saito ko
// @explanation
// オブジェクトを管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "ManagerBase.h"
class UIManager : public ManagerBase
{ 
	public:
	UIManager();
	virtual ~UIManager();
	virtual bool Terminate()override;
	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;

	void AddInput(void* value)override;
	void DeleteName(const std::string& ui)override;
	void DeleteInput(void* value)override;
	void DelAll()override;
	void Sort();

protected:
	std::vector<class UIBase*> _uiList;//UIのリスト
	std::vector<class UIBase*> _addUiList;//追加するUIのリスト
	std::vector<class UIBase*> _delUiList;//削除するUIのリスト
	std::vector<std::string> _delUiNameList;//削除するUIの名前リスト
};