//----------------------------------------------------------------------
// @filename ObjectManager.h
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "ManagerBase.h"
class ObjectManager : public ManagerBase
{
	public:
	ObjectManager();
	~ObjectManager();
	virtual bool Terminate()override;

	void Add(class ObjectBase* object);
	void AddInput(void* value)override;
	void DeleteName(const std::string& name)override;
	void DeleteInput(void* value)override;
	void DelAll()override;

	bool UpdateInit()override;
	bool Update()override;
	bool UpdateEnd()override;
	bool Draw() override;

	class ObjectBase* Get(const std::string& name);
protected:
	std::vector<class ObjectBase*> _addObjectList; //�ǉ�����I�u�W�F�N�g���X�g
	std::vector<class ObjectBase*> _objectList; //�I�u�W�F�N�g���X�g
	std::vector<class ObjectBase*> _delObjectList; //�폜����I�u�W�F�N�g���X�g
	std::vector<std::string> _delObjectNameList; //�폜����I�u�W�F�N�g���O���X�g
};

