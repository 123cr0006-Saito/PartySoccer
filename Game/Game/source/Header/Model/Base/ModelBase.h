#pragma once
#include "DxLib.h"
#include <string>
class ModelBase
{
public:
	ModelBase();
	ModelBase(std::string name, int layer, int handle);
	virtual ~ModelBase();
	void Render();

	// Layer�֘A--------------------------------------
	int GetLayer(){return _layer;};

	// Model�֘A--------------------------------------
	std::string GetName(){return _name;};
	void SetPos(class Vector3D pos);
	void SetModelForwardRotationY(class Vector3D forwardVec);
	void SetScale(class Vector3D scale);
	void SetRotation(class Vector3D rot);
	//-----------------------------------------------------
	
	// Animation�֘A---------------------------------
	void SetAttachAnimBlendRate(int attachIndex, float rate);
	void SetAttachAnimTime(int attachIndex, float time);
	//-----------------------------------------------------
	
	// Shader�֘A-------------------------------------
	void SetIsShader(bool isShader){_isShader = isShader;};
	void SetVertexShader(int vertexHandle){_vertexShader = vertexHandle; };
	void SetPixelShader(int pixelHandle){_pixelShader = pixelHandle;};	
	//-----------------------------------------------------

protected:
	int _modelHandle;
	std::string _name;
	int _layer;

	int _vertexShader;
	int _pixelShader;
	bool _isShader;
};

