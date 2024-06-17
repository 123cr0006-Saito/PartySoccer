#pragma once
#include "Base/UIRotaBase.h"
#include <unordered_map>
class UITimer : public UIRotaBase
{
	public:
	UITimer(class TimeLimit*);
	~UITimer();
	void Draw()override;
protected:
	std::unordered_map<int, int> _timeHandle;
	UIRotaParam _timeHandleParam;
	class TimeLimit* _timer;
};

