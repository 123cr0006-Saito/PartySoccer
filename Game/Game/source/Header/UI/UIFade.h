#pragma once
#include "Base/UIBase.h"
class UIFade : public UIBase
{
public:
	UIFade(int color);
	~UIFade();
	void Draw()override;

	void SetAlpha(int alpha) {_alpha = alpha; }
	int  SetColor(int color) { _color = color; }
protected:
	int _color;
};