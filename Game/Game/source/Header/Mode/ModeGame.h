//----------------------------------------------------------------------
// @filename ModeGame.h
// @author: saito ko
// @explanation
// �Q�[���{�҂��Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "dxlib.h"
#include "../../../AppFrame/source/Application/UtilMacro.h"

class ModeGame : public ModeBase
{
	typedef ModeBase base;

public:
	ModeGame();
	virtual bool Initialize()override;
	virtual bool Terminate()override;
	virtual bool Process()override;
	virtual bool Render()override;

	bool LoadObject();
	bool LoadUI();
	void ReSetGame();
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> LoadObjectParam(const std::string& fileName);
protected:
	class SuperManager* _superManager;//�X�[�p�[�}�l�[�W���[�N���X
	class Player* _player;//�v���C���[�N���X
	class Camera* _camera;//�J�����N���X
	class Score* _score;//�_���N���X
	class TimeLimit* _timeLimit;//���Ԑ����N���X
	std::vector<std::string> _objectName;//�ǂݍ��񂾃I�u�W�F�N�g�̖��O���i�[����ϐ�

	bool _isAddBall;//�{�[����ǉ����邩�ǂ���
	int _currentTime;//���݂̎���
};