#include "../../../Header/UI/Base/UIBase.h"

UIBase::UIBase():
alpha(0)
{

};

UIBase::UIBase(UIParam param){
	pos = param.pos;
	center = param.center;
	extrate = param.extrate;
	angle = param.angle;
	handle = param.handle;
};

UIBase::~UIBase(){

};

void UIBase::Update(){

};

void UIBase::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph3(pos.x ,pos.y,center.x,center.y,extrate.x,extrate.y,angle,handle,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}