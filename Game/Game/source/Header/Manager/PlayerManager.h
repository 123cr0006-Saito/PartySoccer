#pragma once
#include "../../Header/Object/Player/Player.h"
#include "ManagerBase.h"
// @brief プレイヤーの管理クラス
// セレクト画面で決定したキャラクターを管理するクラス　パッドの数でプレイヤーの数を設定
class PlayerManager : public ManagerBase
{
	public:
	PlayerManager();
	~PlayerManager();

	void Add(std::vector<std::tuple<std::string, XInput*, int>> param);
	void DelAll();

	void InitParam();

	void LoadObjectPos();
	
	std::vector<std::pair<std::string, Player*>> GetList() { return _player; }
	int GetListSize()override;

	bool Update()override;
	bool UpdateEnd()override;

	bool Draw()override;
	
protected:
	std::vector<std::pair<std::string,Player*>> _player;
	std::vector<Vector3D> _originPos;
};

