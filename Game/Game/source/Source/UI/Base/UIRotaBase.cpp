#include "../../../Header/UI/Base/UIRotaBase.h"

UIRotaBase::UIRotaBase(UIRotaParam param)
{
	_param._alpha = param._alpha;
	_param._pos = param._pos;
	_param._center = param._center;
	_param._extrate = param._extrate;
	_param._angle = param._angle;
	_param._handle = param._handle;
};

UIRotaBase::~UIRotaBase() {

};

void UIRotaBase::Update() {

};

void UIRotaBase::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _param._alpha);
	float rate = _screenSize.x / 1920;
	DrawRotaGraph3(_param._pos.x * rate, _param._pos.y * rate, _param._center.x * rate, _param._center.y * rate, _param._extrate.x * rate, _param._extrate.y * rate, _param._angle, _param._handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}