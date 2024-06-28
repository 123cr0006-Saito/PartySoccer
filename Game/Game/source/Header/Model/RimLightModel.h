//----------------------------------------------------------------------
// @filename RimLightModel.h
// @author: saito ko
// @explanation
// モデル描画にリムライトを使用するクラス
//----------------------------------------------------------------------
#pragma once
#include "Base/ModelBase.h"
class RimLightModel : public ModelBase
{
public:
	RimLightModel(const std::string& name,const int layer,const int handle);
	virtual ~RimLightModel();
	void SetRimColor(const float r,const float g,const float b);
protected:
	int _rimLightColor;//リムライトの色
};

