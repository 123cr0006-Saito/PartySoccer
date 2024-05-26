#pragma once
#include <utility>
#include <algorithm>
#include <vector>
class ManagerBase
{
	public:
	ManagerBase();
	virtual ~ManagerBase();
	virtual bool Init();
	virtual bool Update();
	virtual bool Draw();
};

