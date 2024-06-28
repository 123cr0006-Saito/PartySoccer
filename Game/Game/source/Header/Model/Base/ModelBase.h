//----------------------------------------------------------------------
// @filename ModelBase.h
// @author: saito ko
// @explanation
// 3Dモデルを管理する基底クラス
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

	// Layer関連--------------------------------------
	int GetLayer() const {return _layer;} ;

	// Model関連--------------------------------------
	std::string GetName() const {return _name;};
	void SetPos(const class Vector3D& pos);
	void SetModelForwardRotationY(const class Vector3D& forwardVec);
	void SetScale(const class Vector3D& scale);
	void SetRotation(const class Vector3D& rot);
	//-----------------------------------------------------
	
	// Animation関連---------------------------------
	void SetAttachAnimBlendRate(const int attachIndex,const float rate);
	void SetAttachAnimTime(const int attachIndex,const float time);
	//-----------------------------------------------------
	
	// Shader関連-------------------------------------
	void SetIsShader(const bool isShader){_isShader = isShader;};
	void SetVertexShader(const int vertexHandle){_vertexShader = vertexHandle; };
	void SetPixelShader(const int pixelHandle){_pixelShader = pixelHandle;};	
	//-----------------------------------------------------

protected:
	int _modelHandle;//モデルハンドル
	std::string _name;//モデル名
	int _layer;//描画順のレイヤー

	int _vertexShader;//頂点シェーダーハンドル
	int _pixelShader;//ピクセルシェーダーハンドル
	bool _isShader;//シェーダーを使用するか
};

