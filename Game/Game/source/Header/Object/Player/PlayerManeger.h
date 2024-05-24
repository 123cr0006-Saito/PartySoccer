#pragma once
#include "Player.h"
#include <vector>
// @brief プレイヤーの管理クラス
// セレクト画面で決定したキャラクターを管理するクラス　パッドの数でプレイヤーの数を設定
class PlayerManeger
{
	static PlayerManeger* _instance;
	public:
	PlayerManeger();
	~PlayerManeger();
	bool Update();
	bool CreatePlayer(std::vector<std::pair<XInput*,int>> param);
	static PlayerManeger* GetInstance() {return _instance;}
protected:
	std::vector<Player*> _player;
};

