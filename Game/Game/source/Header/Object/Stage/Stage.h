//----------------------------------------------------------------------
// @filename Stage.h
// @author: saito ko
// @explanation
// �X�e�[�W�N���X
//----------------------------------------------------------------------
#pragma once
#include "../Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
class Stage : public ObjectBase
{
public:
	Stage(const std::string& name);
	~Stage();
	virtual bool Update()override;
protected:
	class ModelBase* _model;//���f��
};