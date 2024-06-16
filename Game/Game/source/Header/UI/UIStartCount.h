#pragma once
#include "Base/UIBase.h"
#include <unordered_map>
class UIStartCount : public UIBase
{
public:
	UIStartCount();
	~UIStartCount();
	void Update()override;
protected:
	std::unordered_map<int,int> _startCountHandle;
	int _currentTime;
};

