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
	bool Update()override;
	bool Draw()override;
	bool CreatePlayer(std::vector<std::pair<XInput*,int>> param);
	static PlayerManeger* GetInstance() {return _instance;}
protected:
	std::vector<Player*> _player;
};

