//----------------------------------------------------------------------
// @filename UIGameEnd.h
// @author: saito ko
// @explanation
// タイムアップ時に終了画面を描画するUIクラス
//----------------------------------------------------------------------
#pragma once
#include "Base/UIRotaBase.h"
class UIGameEnd : public UIRotaBase
{
public:
	UIGameEnd();
	virtual ~UIGameEnd();
	void Update() override;
};

