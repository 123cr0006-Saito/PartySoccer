//----------------------------------------------------------------------
// @filename RenderManager.cpp
// @author: saito ko
// @explanation
// 3Dモデルの描画を管理するクラス
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
	std::vector<class ModelBase*> _modelList;//描画するモデルのリスト
	std::vector<class ModelBase*> _addModelList;//追加するモデルのリスト
	std::vector<class ModelBase*> _delModelList;//削除するモデルのリスト
	std::vector<std::string> _delModelNameList;//削除するモデルの名前のリスト
};

