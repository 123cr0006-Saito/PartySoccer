//----------------------------------------------------------------------
// @filename ObjectBase.h
// @author: saito ko
// @explanation
// �I�u�W�F�N�g�̊��N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include <string>
class ObjectBase
{
public:
	ObjectBase(const std::string& name);
	virtual ~ObjectBase();

	virtual bool Update();
	virtual bool UpdateEnd();
	virtual bool DebugDraw();

	std::string GetName() const { return _name; }
	Vector3D GetForwardVec() const { return _forwardVec; }
	Vector3D GetPos() const { return _pos; }
	virtual void SetPos(const Vector3D& pos) { _pos = pos; }
	virtual void SetOldPos(const Vector3D& pos) { _oldPos = pos; }
	virtual void SetForwardVec(const Vector3D& forward) { _forwardVec = forward; }
	
protected:
	Vector3D _pos; // ���W
	Vector3D _oldPos; // 1�t���[���O�̍��W
	Vector3D _forwardVec; // �O���x�N�g��
	std::string _name;// ���O
};

