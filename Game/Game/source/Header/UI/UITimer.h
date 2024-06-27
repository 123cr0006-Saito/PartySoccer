#pragma once
#include "Base/UIRotaBase.h"
#include <array>
class UITimer : public UIRotaBase
{
public:
	UITimer(class TimeLimit*);
	~UITimer();
	void Draw()override;
protected:
	std::array<int,10> _timeHandle;
	Vector3D _timeHandlePos;
	Vector3D _timeHandleCenter;

	class TimeLimit* _timer;
};

