//----------------------------------------------------------------------
// @filename UITimer.h
// @author: saito ko
// @explanation
// 残り時間を描画するクラス
//----------------------------------------------------------------------
#pragma once
#include "Base/UIRotaBase.h"
#include <array>
class UITimer : public UIRotaBase
{
public:
	UITimer(class TimeLimit*);
	~UITimer();
	void Draw()override;
protected:
	class TimeLimit* _timer;// 時間制限クラス
	std::array<int,10> _timeHandle;// 残り時間の数字が入る画像ハンドル
	Vector3D _timeHandlePos;// 残り時間の位置
	Vector3D _timeHandleCenter;// 残り時間の中心
};

