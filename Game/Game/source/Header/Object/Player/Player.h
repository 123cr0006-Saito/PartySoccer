#pragma once
#include "../Base/ObjectBase.h"
#include "../../../AppFrame/source/System/Header/Input/XInput.h"
#include <algorithm>
class Player : public ObjectBase
{
	public:
	Player(std::pair<XInput*,int> param);
	~Player();
	virtual bool Init() override;
	virtual bool Update()override;
	protected:
	XInput* _Input;
	int _stamina;
};

