//----------------------------------------------------------------------
// @filename Ball.h
// @author: saito ko
// @explanation
// �{�[���N���X
//----------------------------------------------------------------------
#pragma once
#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Ball : public ObjectBase {
	public:
	Ball(const std::string& name);
	~Ball();
	
	bool Update()override;
	bool UpdateEnd()override;
	bool DebugDraw()override;

	bool GetIsShoot() const { return _isShoot; }
	Sphere* GetSphere() const { return _sphere; }
	float GetSpeed() const { return _speed; }

	void SetPos(const Vector3D& pos) override { _pos = pos; _sphere->pos = pos; };
	void SetSpeed(const float speed) { _speed = speed; }
	void AddSpeed(const float speed) { _speed += speed; }
	void SetPosToOldPos() { _pos = _oldPos; }

	void SetForwardVec(const Vector3D& forwardVec) ;
protected: 
	class ModelBase* _model;//���f��
	bool _isShoot;//�ł��o���ꂽ��
	Sphere* _sphere;//�����蔻��p
	Vector3D _dirVec;//���f���̉�]�l
	float _speed;//���x
	int _gravity; //�d��
};