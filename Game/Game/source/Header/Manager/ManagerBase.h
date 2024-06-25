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
	virtual bool UpdateInit();
	virtual bool Update();
	virtual bool UpdateEnd();
	virtual bool Draw();

	template<typename T>
	void Add(T* value) {
		void* ptr = static_cast<void*>(value);
		AddInput(ptr);
	};

	virtual void AddInput(void* value){};

	virtual void Del(std::string){};
	virtual void DelAll(){};

	int GetID() { return _id; }
	std::string GetName() { return _name; }
	virtual int GetListSize() = 0;

protected:
	int _id;
	std::string _name;
};

