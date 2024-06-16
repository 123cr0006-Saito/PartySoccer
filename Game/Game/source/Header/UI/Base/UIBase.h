#pragma once
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include <string>
class UIBase
{
public:
	struct UIParam {
		int handle;
		Vector3D pos;
		Vector3D center;
		Vector3D extrate;
		float angle;
		Vector3D screenSize;
		int alpha;
	};
public:
	UIBase();
	UIBase(UIParam param);
	virtual ~UIBase();
	virtual void Update();
	virtual void Draw();
	//--------------------------------------
	//ïœêî
	int handle;
	Vector3D pos;
	Vector3D center;
	Vector3D extrate;
	float angle;
	Vector3D screenSize;
	float alpha;
};

