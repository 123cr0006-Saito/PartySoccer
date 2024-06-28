//----------------------------------------------------------------------
// @filename UIFade.h
// @author: saito ko
// @explanation
// フェードイン、フェードアウトを行うクラス
//----------------------------------------------------------------------
#pragma once
#include "Base/UIBase.h"
class UIFade : public UIBase
{
public:
	UIFade(const int color);
	~UIFade();
	void Draw()override;

	void SetAlpha(const int alpha) {_alpha = alpha; }
	int  SetColor(const int color) { _color = color; }
protected:
	int _color;//色
};