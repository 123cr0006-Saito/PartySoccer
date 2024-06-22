#pragma once
#include "Base/UIBase.h"
#include <array>
class UIPlayerParam : public UIBase
{
public:
	UIPlayerParam(class Player* ,std::string, Vector3D);
	virtual ~UIPlayerParam();
	virtual void Update();
	virtual void Draw();
protected:
	class Player* _player;
	std::array<VERTEX2D,4> _staminaGauge;
	std::array<VERTEX2D, 4> _shootGauge;
};

