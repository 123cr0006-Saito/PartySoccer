#pragma once
#include "Player.h"
#include <vector>
// @brief �v���C���[�̊Ǘ��N���X
// �Z���N�g��ʂŌ��肵���L�����N�^�[���Ǘ�����N���X�@�p�b�h�̐��Ńv���C���[�̐���ݒ�
class PlayerManeger
{
	static PlayerManeger* _instance;
	public:
	PlayerManeger();
	~PlayerManeger();
	bool Update();
	bool CreatePlayer(std::vector<std::pair<XInput*,int>> param);
	static PlayerManeger* GetInstance() {return _instance;}
protected:
	std::vector<Player*> _player;
};

