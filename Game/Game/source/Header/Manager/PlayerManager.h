#pragma once
#include "../../Header/Object/Player/Player.h"
#include "ManagerBase.h"
// @brief �v���C���[�̊Ǘ��N���X
// �Z���N�g��ʂŌ��肵���L�����N�^�[���Ǘ�����N���X�@�p�b�h�̐��Ńv���C���[�̐���ݒ�
class PlayerManager : public ManagerBase
{
	public:
	PlayerManager();
	~PlayerManager();

	void Add(std::vector<std::tuple<std::string, XInput*, int>> param);
	void DelAll();

	void InitParam();

	void LoadObjectPos();
	
	std::vector<std::pair<std::string, Player*>> GetList() { return _player; }
	int GetListSize()override;

	bool Update()override;
	bool UpdateEnd()override;

	bool Draw()override;
	
protected:
	std::vector<std::pair<std::string,Player*>> _player;
	std::vector<Vector3D> _originPos;
};

