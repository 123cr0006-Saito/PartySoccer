//----------------------------------------------------------------------
// @filename AnimationBase.h
// @author: saito ko
// @explanation
// UI�A�j���[�V�����̊��N���X
//----------------------------------------------------------------------
#pragma once
#include "../Base/UIRotaBase.h"
class AnimationBase
{
public:
	AnimationBase(UIRotaBase* ui);
	~AnimationBase();
	virtual void Update()= 0;
	virtual void Load(const std::string&) = 0;
protected:
	UIRotaBase* _ui;//UI�̃|�C���^
	int _currentTime;//���݂̎���
	int _endTime;//�I������
	int _delayTime;//�x������
};