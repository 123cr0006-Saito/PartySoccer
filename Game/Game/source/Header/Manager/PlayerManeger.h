#pragma once
#include "../../Header/Object/Player/Player.h"
#include "ManagerBase.h"
// @brief プレイヤーの管理クラス
// セレクト画面で決定したキャラクターを管理するクラス　パッドの数でプレイヤーの数を設定
class PlayerManeger : public ManagerBase
{
	static PlayerManeger* _instance;
	public:
	PlayerManeger();
	~PlayerManeger();

	static PlayerManeger* GetInstance() { return _instance; }
	bool Add(std::vector<std::pair<XInput*, int>> param);
	
	std::string GetListName(std::string name)override;
	int GetListSize()override;

	bool Update()override;
	bool Draw()override;
	
protected:
	std::vector<std::pair<std::string,Player*>> _player;
};

