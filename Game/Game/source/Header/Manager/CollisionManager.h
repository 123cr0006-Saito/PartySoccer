//----------------------------------------------------------------------
// @filename CollisionManager.h
// @author: saito ko
// @explanation
// 当たり判定とそのリアクションを行うクラス
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
	std::vector<CollisionBase*> _addCollisionList; //追加する当たり判定のリスト
	std::vector<CollisionBase*> _collisionList; //当たり判定のリスト
	std::vector<CollisionBase*> _delCollisionList; //削除する当たり判定のリスト
	std::vector<std::string> _delCollisionNameList; //削除する当たり判定の名前のリスト
};

