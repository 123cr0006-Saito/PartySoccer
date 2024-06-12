#pragma once
#include "../Base/ObjectBase.h"
#include "../../../AppFrame/source/System/Header/Input/XInput.h"
#include <string>
#include <utility>
#include <algorithm>
class Player : public ObjectBase
{
public:
	Player(std::string name, std::pair<XInput*,int> param);
	~Player();
	virtual bool Init() override;
	virtual bool Update()override;
	virtual bool DebugDraw()override;

	void SetKnockBack(int knockBack, Vector3D knockBackVec);
	const bool GetIsKnockBack() { return _isKnockBack; }
	const int GetPower() { return _power; }
	const int GetStamina() { return _stamina; }
	const int GetDash() { return _dash; }
	const Vector3D GetForwardVec() { return _forwardVec; }
	XInput* GetInput() { return _Input; }
protected:
	XInput* _Input;
	int _dash; // ダッシュ時のスピード
	int _stamina;
	bool _isTired;
	int _power;
	int _glavity;
	Vector3D _forwardVec;
	Capsule* _capsule;

	bool _isKnockBack;
	int _knockBack;
	Vector3D _knockBackVec;
};

