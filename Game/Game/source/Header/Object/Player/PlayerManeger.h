#pragma once
#include "Player.h"
#include <vector>
// @brief �v���C���[�̊Ǘ��N���X
// �Z���N�g��ʂŌ��肵���L�����N�^�[���Ǘ�����N���X�@�p�b�h�̐��Ńv���C���[�̐���ݒ�
class PlayerManeger
{
	public:
	PlayerManeger();
	~PlayerManeger();
	bool Update();
	bool SelectPlayer();
	bool Render();
protected:
	std::vector<Player*> _player;
};

