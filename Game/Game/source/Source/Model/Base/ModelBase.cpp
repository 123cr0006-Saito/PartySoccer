//----------------------------------------------------------------------
// @filename ModelBase.cpp
// @author: saito ko
// @explanation
// 3D���f�����Ǘ�������N���X
//----------------------------------------------------------------------
#include "../../../Header/Model/Base/ModelBase.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
ModelBase::ModelBase() :
	_name(""),
	_layer(0),
	_modelHandle(0),
	_vertexShader(0),
	_pixelShader(0),
	_isShader(false)
{
};
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param ���f���̖��O
// @param ���C���[�ԍ�
// @param ���f���n���h��
// @return ����
//----------------------------------------------------------------------
ModelBase::ModelBase(const std::string& name, const int layer, const int handle) :
	_name(name),
	_layer(layer),
	_modelHandle(handle),
	_vertexShader(0),
	_pixelShader(0),
	_isShader(false)
{
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
ModelBase::~ModelBase(){

};
//----------------------------------------------------------------------
// @brief ���f���̍��W��ݒ�
// @param ���W
// @return ����
//----------------------------------------------------------------------
void ModelBase::SetPos(const Vector3D& pos){
	MV1SetPosition(_modelHandle, pos.toVECTOR());
};
//----------------------------------------------------------------------
// @brief ���ʕ�����ݒ�
// @param ���ʕ���
// @return ����
//----------------------------------------------------------------------
void ModelBase::SetModelForwardRotationY(const Vector3D& forwardVec){
	Math::SetModelForward_RotationY(_modelHandle, forwardVec.toVECTOR());
};
//----------------------------------------------------------------------
// @brief ���f���̊g�嗦��ݒ�
// @param �g�嗦
// @return ����
//----------------------------------------------------------------------
void ModelBase::SetScale(const Vector3D& scale){
	MV1SetScale(_modelHandle, scale.toVECTOR());
};
//----------------------------------------------------------------------
// @brief ���f���̉�]�l��ݒ�
// @param ��]�l
// @return ����
//----------------------------------------------------------------------
void ModelBase::SetRotation(const Vector3D& rot){
	MV1SetRotationXYZ(_modelHandle, rot.toVECTOR());
};
//----------------------------------------------------------------------
// @brief ���f���̃A�j���[�V�����̃u�����h����ݒ�
// @param �A�j���[�V�����̃C���f�b�N�X
// @param �u�����h��
// @return ����
//----------------------------------------------------------------------
void ModelBase::SetAttachAnimBlendRate(int attachIndex, float rate){
	MV1SetAttachAnimBlendRate(_modelHandle, attachIndex, rate);
};
//----------------------------------------------------------------------
// @brief ���f���̃A�j���[�V�����̎��Ԃ�ݒ�
// @param �A�j���[�V�����̃C���f�b�N�X
// @param ����
// @return ����
//----------------------------------------------------------------------
void ModelBase::SetAttachAnimTime(int attachIndex, float time){
	MV1SetAttachAnimTime(_modelHandle, attachIndex, time);
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
void ModelBase::Render(){
	if(_isShader){
		// �V�F�[�_�[���g�p����
		MV1SetUseOrigShader(true);
		SetUsePixelShader(_pixelShader);
		SetUseVertexShader(_vertexShader);
	}
	// ���f���̕`��
	MV1DrawModel(_modelHandle);
	if (_isShader) {
		// �V�F�[�_�[���g�p���Ȃ�
		MV1SetUseOrigShader(false);
	}
};
