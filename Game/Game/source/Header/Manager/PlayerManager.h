//----------------------------------------------------------------------
// @filename PlayerManager.h
// @author: saito ko
// @explanation
// プレイヤーを管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "ManagerBase.h"
class PlayerManager : public ManagerBase
{
	public:
	PlayerManager();
	~PlayerManager();
	virtual bool Terminate()override;

	void Add(const std::vector<std::tuple<std::string,class XInput*, int>>& param);
	void DelAll();

	void InitParam();
	
	std::vector<class Player*> GetList() { return _player; }

	bool Update()override;
	bool UpdateEnd()override;

	bool Draw()override;
	
protected:
	std::vector<class Player*> _player;//プレイヤーのリスト
};

