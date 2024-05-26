#pragma once
#include "dxlib.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>
class ManagerBase
{
	public:
	virtual ~ManagerBase() = default;

	virtual bool Init();
	virtual bool Update();
	virtual bool Draw();

	int GetID() { return _id; }
	std::string GetName() { return _name; }
	virtual std::string GetListName(std::string name) = 0;
	virtual int GetListSize() = 0;

protected:
	int _id;
	std::string _name;
};

