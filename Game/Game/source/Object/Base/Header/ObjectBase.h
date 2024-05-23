#pragma once
#include "dxlib.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();
	virtual bool Init();
	virtual bool Update();
	virtual bool Render();
protected:
	Vector3D _pos;
	Vector3D _size;
	Vector3D _rot;
	int _modelHandle;
};
