//----------------------------------------------------------------------
// @filename ModeGameEnd.h
// @author: saito ko
// @explanation
// �Q�[���I�����̉��o���s���N���X
//----------------------------------------------------------------------
#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
class ModeGameEnd : public ModeBase
{
public:
	ModeGameEnd();
	~ModeGameEnd();
	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
protected:
	int _currentTime;//���݂̎���
	class UIGameEnd* _ui;//�Q�[���I������UI
};

