//----------------------------------------------------------------------
// @filename ObjectManager.h
// @author: saito ko
// @explanation
// オブジェクトを管理するクラス
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
	std::vector<class ObjectBase*> _addObjectList; //追加するオブジェクトリスト
	std::vector<class ObjectBase*> _objectList; //オブジェクトリスト
	std::vector<class ObjectBase*> _delObjectList; //削除するオブジェクトリスト
	std::vector<std::string> _delObjectNameList; //削除するオブジェクト名前リスト
};

