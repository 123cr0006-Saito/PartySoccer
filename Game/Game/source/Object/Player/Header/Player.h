#pragma once
#include "../../Base/Header/ObjectBase.h"
class Player : public ObjectBase
{
	public:
	Player();
	~Player();
	virtual bool Init() override;
	virtual bool Update()override;
	virtual bool Render()override;
	protected:
};

