//----------------------------------------------------------------------
// @filename RimLightModel.h
// @author: saito ko
// @explanation
// ���f���`��Ƀ������C�g���g�p����N���X
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
	int _rimLightColor;//�������C�g�̐F
};

