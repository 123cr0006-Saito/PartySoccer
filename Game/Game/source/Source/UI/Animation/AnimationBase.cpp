//----------------------------------------------------------------------
// @filename AnimationBase.cpp
// @author: saito ko
// @explanation
// UIアニメーションの基底クラス
//----------------------------------------------------------------------
#include "../../../Header/UI/Animation/AnimationBase.h"
#include "dxlib.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param UIクラスのインスタンス
// @return 無し
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
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
AnimationBase::~AnimationBase(){
	_ui = nullptr;
};