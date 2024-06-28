//----------------------------------------------------------------------
// @filename CollisionManager.h
// @author: saito ko
// @explanation
// �����蔻��Ƃ��̃��A�N�V�������s���N���X
//----------------------------------------------------------------------
#pragma once
#include "ManagerBase.h"
#include "../Object/Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
class CollisionManager:public ManagerBase
{
public:
	CollisionManager();
	~CollisionManager();
	virtual bool Terminate()override;
	void AddInput(void* value)override;
	void DeleteName(const std::string& name)override;
	void DeleteInput(void* value)override;
	void DelAll()override;

	bool UpdateInit()override;
	bool Update()override;
	bool Draw()override;

	bool CollisionCheckForPlayer(CollisionBase*);
	bool CollisionCheckForBall(CollisionBase*);

protected:
	std::vector<CollisionBase*> _addCollisionList; //�ǉ����铖���蔻��̃��X�g
	std::vector<CollisionBase*> _collisionList; //�����蔻��̃��X�g
	std::vector<CollisionBase*> _delCollisionList; //�폜���铖���蔻��̃��X�g
	std::vector<std::string> _delCollisionNameList; //�폜���铖���蔻��̖��O�̃��X�g
};

