//----------------------------------------------------------------------
// @filename ModelBase.h
// @author: saito ko
// @explanation
// 3D���f�����Ǘ�������N���X
//----------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include <string>
class ModelBase
{
public:
	ModelBase();
	ModelBase(const std::string& name,const int layer,const int handle);
	virtual ~ModelBase();
	void Render();

	// Layer�֘A--------------------------------------
	int GetLayer() const {return _layer;} ;

	// Model�֘A--------------------------------------
	std::string GetName() const {return _name;};
	void SetPos(const class Vector3D& pos);
	void SetModelForwardRotationY(const class Vector3D& forwardVec);
	void SetScale(const class Vector3D& scale);
	void SetRotation(const class Vector3D& rot);
	//-----------------------------------------------------
	
	// Animation�֘A---------------------------------
	void SetAttachAnimBlendRate(const int attachIndex,const float rate);
	void SetAttachAnimTime(const int attachIndex,const float time);
	//-----------------------------------------------------
	
	// Shader�֘A-------------------------------------
	void SetIsShader(const bool isShader){_isShader = isShader;};
	void SetVertexShader(const int vertexHandle){_vertexShader = vertexHandle; };
	void SetPixelShader(const int pixelHandle){_pixelShader = pixelHandle;};	
	//-----------------------------------------------------

protected:
	int _modelHandle;//���f���n���h��
	std::string _name;//���f����
	int _layer;//�`�揇�̃��C���[

	int _vertexShader;//���_�V�F�[�_�[�n���h��
	int _pixelShader;//�s�N�Z���V�F�[�_�[�n���h��
	bool _isShader;//�V�F�[�_�[���g�p���邩
};

