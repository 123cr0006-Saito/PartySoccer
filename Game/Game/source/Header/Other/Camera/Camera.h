//----------------------------------------------------------------------
// @filename Camera.cpp
// @author: saito ko
// @explanation
// カメラを制御するクラス
//----------------------------------------------------------------------
#pragma once
#include "../../../AppFrame/source/System/Header/Function/Vector3D.h"
#include <utility>
class Camera
{
public:
	Camera();
	~Camera();
	bool Update();
	void UpdateSelectAndResult();
	void UpdateGame();
	bool Draw();

	static Camera* GetInstance() { return _instance; }

	void SetIsGame(const bool isGame) {_isGame = isGame;};
	void SetPos(const Vector3D& pos) { _pos.first = pos; }
	void SetTarget(const Vector3D& target) { _pos.second = target; }
	bool SpringDamperSystem(Vector3D& nowPos,const Vector3D& targetPos, Vector3D& speed,const double time);

private:
	class PlayerManager* _player;//プレイヤーの情報を取得するためのポインタ
	static Camera* _instance;//このクラスのインスタンス
	std::pair<Vector3D, Vector3D> _pos; // <カメラ位置,注視点>
	Vector3D _targetSpeed;//カメラの移動速度
	Vector3D _cameraSpeed;//カメラの移動速度
	bool _isGame;//メインゲームかどうか
};

