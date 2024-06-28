//----------------------------------------------------------------------
// @filename UIPlayerParam.h
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "Base/UIBase.h"
#include <array>
class UIPlayerParam : public UIBase
{
public:
	UIPlayerParam(class Player* player ,const std::string& name, const Vector3D& pos);
	virtual ~UIPlayerParam();
	virtual void Update();
	virtual void Draw();
protected:
	class Player* _player;// �v���C���[�N���X
	std::array<VERTEX2D, 4> _staminaGauge;// �X�^�~�i�Q�[�W�̒��_
	std::array<VERTEX2D, 4> _shootGauge;// �V���[�g�Q�[�W�̒��_
};

