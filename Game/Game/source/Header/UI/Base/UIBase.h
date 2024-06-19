#pragma once
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include <string>
class UIBase
{
public:
	UIBase();
	UIBase(Vector3D,float,int);
	virtual ~UIBase();
	virtual void Update();
	virtual void Draw();

	Vector3D GetPos() { return _pos; }
	float GetAlpha() { return _alpha; }
	void SetHandle(int handle) { _handle = handle; }
	void SetPos(Vector3D pos) { _pos = pos; }
	void SetAlpha(float alpha) { _alpha = alpha; }
	void SetPosX(float x) { _pos.x = x; }
	void SetPosY(float y) { _pos.y = y; }
protected:
	static Vector3D _screenSize;
	int _handle;
	Vector3D _pos;
	float _alpha;
};