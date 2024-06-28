//----------------------------------------------------------------------
// @filename IterationAnim.h
// @author: saito ko
// @explanation
// sin波を使ったxとyが移動するアニメーション
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
	Vector3D _originPos;//初期位置
	Vector3D _movePos;//移動量
	int _cycleTime;//周期
};