#pragma once
#include "ManagerBase.h"
// @brief �v���C���[�̊Ǘ��N���X
// �Z���N�g��ʂŌ��肵���L�����N�^�[���Ǘ�����N���X�@�p�b�h�̐��Ńv���C���[�̐���ݒ�
class PlayerManager : public ManagerBase
{
	public:
	PlayerManager();
	~PlayerManager();
	virtual bool Terminate()override;

	void Add(std::vector<std::tuple<std::string,class XInput*, int>> param);
	void DelAll();

	void InitParam();

	void LoadObjectPos();
	
	std::vector<class Player*> GetList() { return _player; }
	int GetListSize()override;

	bool Update()override;
	bool UpdateEnd()override;

	bool Draw()override;
	
protected:
	std::vector<class Player*> _player;
	std::vector<class Vector3D> _originPos;
};

