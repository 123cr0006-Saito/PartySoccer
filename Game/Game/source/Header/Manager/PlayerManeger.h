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

	static PlayerManeger* GetInstance() { return _instance; }
	bool Add(std::vector<std::pair<XInput*, int>> param);
	
	std::string GetListName(std::string name)override;
	int GetListSize()override;

	bool Update()override;
	bool Draw()override;
	
protected:
	std::vector<std::pair<std::string,Player*>> _player;
};

