#pragma once
#include "Base/UIRotaBase.h"
#include <array>
class UIStartCount : public UIRotaBase
{
public:
	UIStartCount();
	~UIStartCount();
	void Update()override;
protected:
	std::array<int,3> _startCountHandle;
	int _currentTime;
};

