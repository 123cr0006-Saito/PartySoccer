#pragma once
#include "../../Header/Object/Player/Player.h"
#include "ManagerBase.h"
// @brief �v���C���[�̊Ǘ��N���X
// �Z���N�g��ʂŌ��肵���L�����N�^�[���Ǘ�����N���X�@�p�b�h�̐��Ńv���C���[�̐���ݒ�
class PlayerManeger : public ManagerBase
{
	static PlayerManeger* _instance;
	public:
	PlayerManeger();
	~PlayerManeger();
	bool Update()override;
	bool Draw()override;
	bool CreatePlayer(std::vector<std::pair<XInput*,int>> param);
	static PlayerManeger* GetInstance() {return _instance;}
protected:
	std::vector<Player*> _player;
};

