#include "../../../Header/UI/Base/UIBase.h"
#include "../AppFrame/source/Application/Global.h"

#if !defined(_DEBUG) || defined(FULLSCREEN)
Vector3D UIBase::_screenSize = Vector3D(1920, 1080, 0);
#else
Vector3D UIBase::_screenSize = Vector3D(1280, 720, 0);
#endif

UIBase::UIBase(){
	_alpha = 255;
	_handle = -1;
};

UIBase::UIBase(Vector3D pos, float alpha, int handle) :
_pos(pos),
_alpha(alpha),
_handle(handle)
{

};

UIBase::~UIBase(){

};

void UIBase::Update(){

};

void UIBase::Draw(){

};

