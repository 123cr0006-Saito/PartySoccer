//----------------------------------------------------------------------
// @filename UITimer.h
// @author: saito ko
// @explanation
// �c�莞�Ԃ�`�悷��N���X
//----------------------------------------------------------------------
#pragma once
#include "Base/UIRotaBase.h"
#include <array>
class UITimer : public UIRotaBase
{
public:
	UITimer(class TimeLimit*);
	~UITimer();
	void Draw()override;
protected:
	class TimeLimit* _timer;// ���Ԑ����N���X
	std::array<int,10> _timeHandle;// �c�莞�Ԃ̐���������摜�n���h��
	Vector3D _timeHandlePos;// �c�莞�Ԃ̈ʒu
	Vector3D _timeHandleCenter;// �c�莞�Ԃ̒��S
};

