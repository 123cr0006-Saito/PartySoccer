#pragma once
#include "Base/UIRotaBase.h"
#include <unordered_map>
class UIStartCount : public UIRotaBase
{
public:
	UIStartCount();
	~UIStartCount();
	void Update()override;
protected:
	std::unordered_map<int,int> _startCountHandle;
	int _currentTime;
};

