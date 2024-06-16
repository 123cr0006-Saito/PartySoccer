#pragma once
#include "../../Header/Object/Player/Player.h"
#include "ManagerBase.h"
// @brief プレイヤーの管理クラス
// セレクト画面で決定したキャラクターを管理するクラス　パッドの数でプレイヤーの数を設定
class PlayerManeger : public ManagerBase
{
	public:
	PlayerManeger();
	~PlayerManeger();

	void Add(std::vector<std::pair<XInput*, int>> param);

	void SetPos();
	
	std::vector<std::pair<std::string, Player*>> GetList() { return _player; }
	int GetListSize()override;

	bool Update()override;
	bool Draw()override;
	
protected:
	std::vector<std::pair<std::string,Player*>> _player;
};

