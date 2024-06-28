//----------------------------------------------------------------------
// @filename UIRotaBase.h
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "UIBase.h"
#include <vector>

class UIRotaBase : public UIBase
{
public:
	UIRotaBase();
	UIRotaBase(const std::string& name,const Vector3D& pos,const Vector3D& center,const Vector3D& extrate,const float angle,const int alpha,const int handle,const int layer);
	virtual ~UIRotaBase();
	void Update()override;
	void Draw()override;

	void SetAnimation(class AnimationBase* anim) { _animation.emplace_back(anim); }

	
	Vector3D GetCenter() const { return _center; }
	Vector3D GetExtrate() const { return _extrate; }
	float GetAngle() const { return _angle; }

	void SetExtrateX(const float x) { _extrate.x = x; }
	void SetExtrateY(const float y) { _extrate.y = y; }
	void SetAngle(const float angle) { _angle = angle; }
	//--------------------------------------
	//�ϐ�
protected:
	std::vector<class AnimationBase*> _animation;//�A�j���[�V����
	Vector3D _center;//���S
	Vector3D _extrate;//�g�嗦
	float _angle;//��]�l
};