//----------------------------------------------------------------------
// @filename Ball.h
// @author: saito ko
// @explanation
// ボールクラス
//----------------------------------------------------------------------
#pragma once
#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Ball : public ObjectBase {
	public:
	Ball(const std::string& name);
	~Ball();
	
	bool Update()override;
	bool UpdateEnd()override;
	bool DebugDraw()override;

	bool GetIsShoot() const { return _isShoot; }
	Sphere* GetSphere() const { return _sphere; }
	float GetSpeed() const { return _speed; }

	void SetPos(const Vector3D& pos) override { _pos = pos; _sphere->pos = pos; };
	void SetSpeed(const float speed) { _speed = speed; }
	void AddSpeed(const float speed) { _speed += speed; }
	void SetPosToOldPos() { _pos = _oldPos; }

	void SetForwardVec(const Vector3D& forwardVec) ;
protected: 
	class ModelBase* _model;//モデル
	bool _isShoot;//打ち出されたか
	Sphere* _sphere;//当たり判定用
	Vector3D _dirVec;//モデルの回転値
	float _speed;//速度
	int _gravity; //重力
};