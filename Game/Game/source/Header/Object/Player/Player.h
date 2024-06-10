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
protected:
	XInput* _Input;
	int _stamina;
	Vector3D _forwardVec;
	Capsule* _capsule;
};

