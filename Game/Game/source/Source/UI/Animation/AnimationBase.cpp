//----------------------------------------------------------------------
// @filename AnimationBase.cpp
// @author: saito ko
// @explanation
// UI�A�j���[�V�����̊��N���X
//----------------------------------------------------------------------
#include "../../../Header/UI/Animation/AnimationBase.h"
#include "dxlib.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param UI�N���X�̃C���X�^���X
// @return ����
//----------------------------------------------------------------------
AnimationBase::AnimationBase(UIRotaBase* ui):
 _ui(ui),
 _currentTime(GetNowCount()),
 _endTime(0),
 _delayTime(0),
 _isEnd(false)
{
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
AnimationBase::~AnimationBase(){
	_ui = nullptr;
};