#pragma once
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include <string>

class UIParam {
public:
	UIParam() {
		_handle = -1;
		_alpha = 255;
	}
public:
	int _handle;
	Vector3D _pos;
	float _alpha;
};

class UIBase
{
public:
	UIBase();
	virtual ~UIBase();
	virtual void Update();
	virtual void Draw();
protected:
	static Vector3D _screenSize;
};




