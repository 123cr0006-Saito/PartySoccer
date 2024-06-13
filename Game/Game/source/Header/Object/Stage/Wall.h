#pragma once
#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Wall :public ObjectBase
{
	public:
	Wall();
	~Wall();
	void SetColPos(Vector3D pos) { _obb->pos = pos; }
	void SetColLength(Vector3D length) { _obb->SetLength(length); }
	void SetName(std::string name) { _obb->SetName(name); }
	void SetForwardVec(Vector3D vec) { _forwardVec = vec; }
	Vector3D GetForwardVec() { return _forwardVec; }
protected:
	OBB* _obb;
	Vector3D _forwardVec;
};

