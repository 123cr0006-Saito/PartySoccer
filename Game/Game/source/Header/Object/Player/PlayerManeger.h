#pragma once
#include "Player.h"
#include <vector>
// @brief プレイヤーの管理クラス
// セレクト画面で決定したキャラクターを管理するクラス　パッドの数でプレイヤーの数を設定
class PlayerManeger
{
	public:
	PlayerManeger();
	~PlayerManeger();
	bool Update();
	bool SelectPlayer();
	bool Render();
protected:
	std::vector<Player*> _player;
};

