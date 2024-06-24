#pragma once
#include "dxlib.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
#include <string>
class ObjectBase
{
public:
	ObjectBase(std::string name);
	virtual ~ObjectBase();
	virtual bool Init();
	virtual bool UpdateInit();
	virtual bool Update();
	virtual bool UpdateEnd();
	virtual bool DebugDraw();

	std::string GetName() { return _name; }
	Vector3D GetForwardVec() { return _forwardVec; }
	Vector3D GetPos() { return _pos; }
	void SetPos(Vector3D pos) { _pos = pos; }
	void SetOldPos(Vector3D pos) { _oldPos = pos; }
	void SetForwardVec(Vector3D forward) { _forwardVec = forward; }
	
protected:
	Vector3D _pos;
	Vector3D _oldPos;
	Vector3D _forwardVec;
	std::string _name;
};

