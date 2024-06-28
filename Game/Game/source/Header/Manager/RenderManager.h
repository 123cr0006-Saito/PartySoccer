//----------------------------------------------------------------------
// @filename RenderManager.cpp
// @author: saito ko
// @explanation
// 3D���f���̕`����Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "ManagerBase.h"
class RenderManager : public ManagerBase
{
public :
	RenderManager();
	~RenderManager();
	virtual bool Terminate()override;
	void AddInput(void* value)override;
	void DeleteName(const std::string& name)override;
	void DeleteInput(void* value)override;
	void DelAll()override;
	void Sort();

	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;
	
protected:
	std::vector<class ModelBase*> _modelList;//�`�悷�郂�f���̃��X�g
	std::vector<class ModelBase*> _addModelList;//�ǉ����郂�f���̃��X�g
	std::vector<class ModelBase*> _delModelList;//�폜���郂�f���̃��X�g
	std::vector<std::string> _delModelNameList;//�폜���郂�f���̖��O�̃��X�g
};

