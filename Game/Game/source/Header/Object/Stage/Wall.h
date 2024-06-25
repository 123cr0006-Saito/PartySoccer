#pragma once
#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Wall :public ObjectBase
{
public:
	Wall(std::string name,Vector3D pos, Vector3D length);
	~Wall();
protected:
	OBB* _obb;
};

