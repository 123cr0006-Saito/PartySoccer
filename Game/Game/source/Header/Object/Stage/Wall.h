//----------------------------------------------------------------------
// @filename Wall.h
// @author: saito ko
// @explanation
// �ǃN���X
//----------------------------------------------------------------------
#pragma once
#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Wall :public ObjectBase
{
public:
	Wall(const std::string& name,const Vector3D& pos,const Vector3D& length);
	~Wall();
protected:
	OBB* _obb;//�����蔻��p
};

