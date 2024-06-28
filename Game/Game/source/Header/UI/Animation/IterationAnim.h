//----------------------------------------------------------------------
// @filename IterationAnim.h
// @author: saito ko
// @explanation
// sin�g���g����x��y���ړ�����A�j���[�V����
//----------------------------------------------------------------------
#pragma once
#include "AnimationBase.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
class IterationAnim : public AnimationBase
{
public:
	IterationAnim(UIRotaBase* ui,const std::string& name,const bool isRandom = false);
	virtual ~IterationAnim();
	void Update()override;
	void Load(const std::string& path)override;
protected:
	Vector3D _originPos;//�����ʒu
	Vector3D _movePos;//�ړ���
	int _cycleTime;//����
};