//----------------------------------------------------------------------
// @filename UIManager.h
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
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
	std::vector<class UIBase*> _uiList;//UI�̃��X�g
	std::vector<class UIBase*> _addUiList;//�ǉ�����UI�̃��X�g
	std::vector<class UIBase*> _delUiList;//�폜����UI�̃��X�g
	std::vector<std::string> _delUiNameList;//�폜����UI�̖��O���X�g
};