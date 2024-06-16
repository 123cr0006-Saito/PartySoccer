#include "../../../Header/UI/Base/UIBase.h"
#include "../AppFrame/source/Application/Global.h"

#if !defined(_DEBUG) || defined(FULLSCREEN)
Vector3D UIBase::screenSize = Vector3D(1920, 1080, 0);
#else
Vector3D UIBase::screenSize = Vector3D(1280, 720, 0);
#endif

UIBase::UIBase() 
{
	param.alpha = 0;
	param.extrate = Vector3D(1, 1, 1);
	param.angle = 0.0f;
	param.handle = 0;
};

UIBase::UIBase(UIParam param)
{
	this->param.alpha = param.alpha;
	this->param.pos = param.pos;
	this->param.center = param.center;
	this->param.extrate = param.extrate;
	this->param.angle = param.angle;
	this->param.handle = param.handle;
};

UIBase::~UIBase(){

};

void UIBase::Update(){

};

void UIBase::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, param.alpha);
	float rate = screenSize.x / 1920; 
	DrawRotaGraph3(param.pos.x * rate , param.pos.y * rate, param.center.x * rate, param.center.y * rate, param.extrate.x * rate, param.extrate.y * rate , param.angle, param.handle,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}