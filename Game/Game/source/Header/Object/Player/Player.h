#pragma once
#include "../Base/ObjectBase.h"
#include "../../../AppFrame/source/System/Header/Input/XInput.h"
class Player : public ObjectBase
{
	public:
	Player();
	~Player();
	virtual bool Init() override;
	virtual bool Update()override;
	protected:
	XInput* _Input;
	int _stamina;
};

