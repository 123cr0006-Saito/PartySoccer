#pragma once
#include "Base/UIBase.h"
#include <unordered_map>
class UITimer : public UIBase
{
	public:
	UITimer(class TimeLimit*);
	~UITimer();
	void Draw()override;
protected:
	std::unordered_map<int, int> _timeHandle;
	UIParam _timeHandleParam;
	class TimeLimit* _timer;
};

