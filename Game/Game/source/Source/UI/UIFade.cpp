//----------------------------------------------------------------------
// @filename UIFade.cpp
// @author: saito ko
// @explanation
// フェードイン、フェードアウトを行うクラス
//----------------------------------------------------------------------
#include "../../Header/UI/UIFade.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param フェードの色
// @return 無し
//----------------------------------------------------------------------
UIFade::UIFade(int color){
	_alpha = 0;
	_color = color;
	_layer = 999999;
	_name = "Fade";
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
UIFade::~UIFade(){

};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 無し
//----------------------------------------------------------------------
void UIFade::Draw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,_alpha);
	DrawBox(0,0, _screenSize.x, _screenSize.y,_color,true );
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,_alpha);
};
