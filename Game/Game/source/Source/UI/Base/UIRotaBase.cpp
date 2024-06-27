//----------------------------------------------------------------------
// @filename UIRotaBase.cpp
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../../Header/UI/Base/UIRotaBase.h"
#include "../../../Header/UI/Animation/AnimationBase.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIRotaBase::UIRotaBase() :
	UIBase(),
	_extrate(Vector3D(1, 1, 1)),
	_angle(0)
{
};
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param �I�u�W�F�N�g�̖��O
// @param �ʒu
// @param ���S
// @param �g�嗦
// @param �p�x
// @param �����x
// @param �摜�n���h��
// @param ���C���[
// @return ����
//----------------------------------------------------------------------
UIRotaBase::UIRotaBase(std::string name,Vector3D pos,Vector3D center, Vector3D extrate,float angle, int alpha, int handle,int layer):
UIBase(name,pos,alpha,handle,layer),
_center(center),
_extrate(extrate),
_angle(angle)
{
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIRotaBase::~UIRotaBase() {
	if (!_animation.empty()) {
		for (auto&& list : _animation) {
			delete list;
		}
	}
	_animation.clear();
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return ����
//----------------------------------------------------------------------
void UIRotaBase::Update() {
	if(!_animation.empty()){
		for(auto&& list : _animation){
			list->Update();
		}
	}
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return ����
//----------------------------------------------------------------------
void UIRotaBase::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	float rate = _screenSize.x / 1920;
	DrawRotaGraph3(_pos.x * rate, _pos.y * rate, _center.x * rate, _center.y * rate, _extrate.x * rate, _extrate.y * rate, _angle, _handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}