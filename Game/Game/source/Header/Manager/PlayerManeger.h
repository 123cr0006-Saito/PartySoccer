#pragma once
#include "../../Header/Object/Player/Player.h"
#include "ManagerBase.h"
// @brief �v���C���[�̊Ǘ��N���X
// �Z���N�g��ʂŌ��肵���L�����N�^�[���Ǘ�����N���X�@�p�b�h�̐��Ńv���C���[�̐���ݒ�
class PlayerManeger : public ManagerBase
{
	public:
	PlayerManeger();
	~PlayerManeger();

	void Add(std::vector<std::pair<XInput*, int>> param);

	void SetPos();
	
	std::vector<std::pair<std::string, Player*>> GetList() { return _player; }
	int GetListSize()override;

	bool Update()override;
	bool Draw()override;
	
protected:
	std::vector<std::pair<std::string,Player*>> _player;
};

