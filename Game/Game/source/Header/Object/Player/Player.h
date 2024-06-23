#pragma once
#include "../Base/ObjectBase.h"
#include <string>
#include <utility>
#include <algorithm>
class Player : public ObjectBase
{
public:
	Player(std::string,class XInput*,int);
	~Player();
	virtual bool Init() override;
	virtual bool Update()override;
	virtual bool UpdateEnd()override;
	void AnimationUpdate(const Vector3D& moveDir);
	virtual bool DebugDraw()override;

	void SetKnockBack(int knockBack, Vector3D knockBackVec);
	void SetPower(int power) { _power = power; }
	void SetStamina(int stamina) { _stamina = stamina; }

	const bool GetIsKnockBack() { return _isKnockBack; }
	const int GetPower() { return _power; }
	const int GetStamina() { return _stamina; }
	const int GetDash() { return _dash; }
	const Vector3D GetForwardVec() { return _forwardVec; }
protected:

	class XInput* _Input; // 入力
	class RimLightModel* _model; // モデル

	int _dash; // ダッシュ時のスピード
	int _stamina; // プレイヤーのスタミナ
	bool _isTired; // 疲れているかどうか
	bool _isShoot; // シュートを打ったかどうか
	int _power;	// プレイヤーの攻撃力
	int _glavity; // 重力

	Vector3D _forwardVec; // 前方向のベクトル
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

