//----------------------------------------------------------------------
// @filename AnimationBase.h
// @author: saito ko
// @explanation
// UIアニメーションの基底クラス
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
	UIRotaBase* _ui;//UIのポインタ
	int _currentTime;//現在の時間
	int _endTime;//終了時間
	int _delayTime;//遅延時間
};