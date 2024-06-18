#pragma once
#include "UIBase.h"

class UIRotaParam : public UIParam {
public:
	UIRotaParam() : UIParam(){
		_angle = 0;
	}
public:
	Vector3D _center;
	Vector3D _extrate;
	float _angle;
};

class UIRotaBase : public UIBase
{
public:
	UIRotaBase() { _param._extrate = Vector3D(1,1,1); };
	UIRotaBase(UIRotaParam param);
	virtual ~UIRotaBase();
	void Update()override;
	void Draw()override;

	void SetParam(UIRotaParam param) { _param = param; }
	UIRotaParam GetParam() { return _param; }
	UIRotaParam* GetParamPtr() { return &_param; }
	//--------------------------------------
	//ïœêî
protected:
	UIRotaParam _param;
};

