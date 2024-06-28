//----------------------------------------------------------------------
// @filename UIStartCount.h
// @author: saito ko
// @explanation
// ゲーム開始時にカウントダウンを行うクラス
//----------------------------------------------------------------------
#pragma once
#include "Base/UIRotaBase.h"
#include <array>
class UIStartCount : public UIRotaBase
{
public:
	UIStartCount();
	~UIStartCount();
	void Update()override;
protected:
	std::array<int,4> _startCountHandle;//スタートカウントのハンドル
	int _currentTime;//現在の時間
};

