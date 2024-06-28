//----------------------------------------------------------------------
// @filename ModeResult.h
// @author: saito ko
// @explanation
// �N���A��ʂ̃N���X
//----------------------------------------------------------------------
#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
class ModeResult : public ModeBase
{
public:
	ModeResult();
	virtual ~ModeResult();

	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;
protected:
	class SuperManager* _superManager; // �X�[�p�[�}�l�[�W���[�N���X
	class PlayerManager* _playerManager; // �v���C���[�}�l�[�W���[�N���X
	class Score* _score; //�_���N���X
	class XInput* _input;//���̓N���X
	class Camera* _camera;//�J�����N���X
	std::string _winnerTeam; //�����`�[���̖��O
	int _currentTime;//���݂̎���
};

