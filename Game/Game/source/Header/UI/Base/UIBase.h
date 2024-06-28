#pragma once
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include <string>
class UIBase
{
public:
	UIBase();
	UIBase(const std::string& name ,const Vector3D& pos,const float alpha,const int handle,const int layer);
	UIBase(const std::string& name ,const Vector3D& pos,const float expansion,const float alpha,const int handle,const int layer);
	virtual ~UIBase();
	virtual void Update();
	virtual void Draw();

	Vector3D GetPos() const { return _pos; }
	std::string GetName() const { return _name; }
	float GetAlpha() const { return _alpha; }
	int GetLayer() const { return _layer; }
	void SetHandle(const int handle) { _handle = handle; }
	void SetPos(const Vector3D& pos) { _pos = pos; }
	void SetAlpha(const float alpha) { _alpha = alpha; }
	void SetPosX(const float x) { _pos.x = x; }
	void SetPosY(const float y) { _pos.y = y; }
protected:
	static Vector3D _screenSize;
	std::string _name;
	int _handle;
	int _layer;
	Vector3D _pos;
	float _alpha;
private:
	float _expansionRate;
};