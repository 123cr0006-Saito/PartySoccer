#pragma once
#include "Base/UIBase.h"
class UIFade : public UIBase
{
public:
	UIFade(int);
	~UIFade();
	void Draw()override;

	int* LinkAlpha() { return &_alpha; }
	int  SetColor(int color) { _color = color; }
protected:
	int _alpha;
	int _color;
};


