#include "../../Header/UI/UIFade.h"

UIFade::UIFade(int color){
	_alpha = 0;
	_color = color;
};

UIFade::~UIFade(){

};

void UIFade::Draw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,_alpha);
	DrawBox(0,0, _screenSize.x, _screenSize.y,_color,true );
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,_alpha);
};
