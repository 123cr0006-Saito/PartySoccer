//----------------------------------------------------------------------
// @filename Player.h
// @author: saito ko
// @explanation
// プレイヤークラス
//----------------------------------------------------------------------
#pragma once
#include "../Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
#include <string>
#include <utility>
#include <algorithm>
class Player : public ObjectBase
{
public:
	Player(const std::string& name ,class XInput* input,const int handle);
	~Player();

	virtual bool Update()override;
	bool UpdateGame();
	virtual bool UpdateEnd()override;

	void MoveUpdate(const Vector3D& normalDir);
	void ShootUpdate();
	void DashUpdate();
	void GravityUpdate();
	void AnimationUpdate(const Vector3D& normalDir);

	virtual bool DebugDraw()override;

	void SetKnockBack(const int knockBack, const Vector3D& knockBackVec);
	void SetPower(const int power) { _power = power; }
	void SetStamina(const int stamina) { _stamina = stamina; }
	void SetIsGame(const bool isGame) { _isGame = isGame; }

	bool GetIsKnockBack() const { return _isKnockBack; }
	int GetPower() const { return _power; }
	int GetStamina() const { return _stamina; }
	int GetDash() const { return _dash; }
	Capsule* GetCapsule() const { return _capsule; }
protected:
	class XInput* _Input; // 入力
	class RimLightModel* _model; // モデル

	int _dash; // ダッシュ時のスピード
	int _stamina; // プレイヤーのスタミナ
	int _power;	// プレイヤーの攻撃力
	int _glavity; // 重力

	bool _isTired; // 疲れているかどうか
	bool _isShoot; // シュートを打ったかどうか
	bool _isPowerMax; // パワーが最大かどうか
	bool _isGame;//メインゲームかどうか

	Capsule* _capsule; // 当たり判定

	bool _isKnockBack; // ノックバック中かどうか
	int _knockBack; // ノックバックの強さ
	Vector3D _knockBackVec; // ノックバックの方向

	//アニメーション
	int _animIndex;// アニメーションハンドル
	float _totalTime;// アニメーションの総再生時間
	float _playTime;// アニメーションの再生時間
	float _animBlendRate;// アニメーションのブレンドレート
};

