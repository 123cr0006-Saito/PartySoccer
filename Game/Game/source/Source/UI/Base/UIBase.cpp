//----------------------------------------------------------------------
// @filename UIBase.cpp
// @author: saito ko
// @explanation
// UI�̊��N���X
//----------------------------------------------------------------------
#include "../../../Header/UI/Base/UIBase.h"
#include "../AppFrame/source/Application/Global.h"
//----------------------------------------------------------------------
// ��ʃT�C�Y���擾
#if !defined(_DEBUG) || defined(FULLSCREEN)
Vector3D UIBase::_screenSize = Vector3D(1920, 1080, 0);
#else
Vector3D UIBase::_screenSize = Vector3D(1280, 720, 0);
#endif
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIBase::UIBase() :
	_name(""),
	_expansionRate(1.0f),
	_alpha(255),
	_layer(0),
	_handle(-1)
{
};
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param ���O
// @param ���W
// @param �����x
// @param �摜�n���h��
// @param ���C���[
// @return ����
//----------------------------------------------------------------------
UIBase::UIBase(std::string name,Vector3D pos, float alpha, int handle, int layer) :
	_name(name),
	_pos(pos),
	_alpha(alpha),
	_handle(handle),
	_layer(layer)
{

};
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param ���O
// @param ���W
// @param �g�嗦
// @param �����x
// @param �摜�n���h��
// @param ���C���[
// @return ����
//----------------------------------------------------------------------
UIBase::UIBase(std::string name,Vector3D pos, float expansion, float alpha, int handle, int layer) :
	_name(name),
	_pos(pos),
	_expansionRate(expansion),
	_alpha(alpha),
	_handle(handle),
	_layer(layer)
{

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIBase::~UIBase(){

};
//----------------------------------------------------------------------
// @brief �X�V����
// @return ����
//----------------------------------------------------------------------
void UIBase::Update(){

};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return ����
//----------------------------------------------------------------------
void UIBase::Draw(){
	float rate = _screenSize.x / 1920;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	DrawRotaGraph(_pos.x * rate,_pos.y * rate, _expansionRate * rate,0.0f,_handle,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

