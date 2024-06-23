#include "../../../Header/Model/Base/ModelBase.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
ModelBase::ModelBase() :
	_name(""),
	_modelHandle(0),
	_vertexShader(0),
	_pixelShader(0),
	_isShader(false)
{
};

ModelBase::ModelBase(std::string name,int handle) :
	_name(name),
	_modelHandle(handle),
	_vertexShader(0),
	_pixelShader(0),
	_isShader(false)
{
};

ModelBase::~ModelBase(){

};

void ModelBase::SetPos(Vector3D pos){
	MV1SetPosition(_modelHandle, pos.toVECTOR());
};

void ModelBase::SetModelForwardRotationY(Vector3D forwardVec){
	Math::SetModelForward_RotationY(_modelHandle, forwardVec.toVECTOR());
};

void ModelBase::SetScale(class Vector3D scale){
	MV1SetScale(_modelHandle, scale.toVECTOR());
};

void ModelBase::SetRotation(class Vector3D rot){
	MV1SetRotationXYZ(_modelHandle, rot.toVECTOR());
};

void ModelBase::SetAttachAnimBlendRate(int attachIndex, float rate){
	MV1SetAttachAnimBlendRate(_modelHandle, attachIndex, rate);
};

void ModelBase::SetAttachAnimTime(int attachIndex, float time){
	MV1SetAttachAnimTime(_modelHandle, attachIndex, time);
};

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
