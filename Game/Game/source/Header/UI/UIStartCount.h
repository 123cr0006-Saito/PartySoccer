//----------------------------------------------------------------------
// @filename UIStartCount.h
// @author: saito ko
// @explanation
// �Q�[���J�n���ɃJ�E���g�_�E�����s���N���X
//----------------------------------------------------------------------
#pragma once
#include "Base/UIRotaBase.h"
#include <array>
class UIStartCount : public UIRotaBase
{
public:
	UIStartCount();
	~UIStartCount();
	void Update()override;
protected:
	std::array<int,4> _startCountHandle;//�X�^�[�g�J�E���g�̃n���h��
	int _currentTime;//���݂̎���
};

