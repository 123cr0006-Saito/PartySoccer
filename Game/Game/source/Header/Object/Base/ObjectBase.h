#pragma once
#include "dxlib.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include <string>
class ObjectBase
{
public:
	ObjectBase(std::string name);
	virtual ~ObjectBase();
	virtual bool Init();
	virtual bool Update();

	bool SetModelAndLayer(int modelHandle, int layer);
	std::string GetName() { return _name; }
	
protected:
	Vector3D _pos;
	Vector3D _size;
	Vector3D _rot;
	std::string _name;
	int _modelHandle;
};

