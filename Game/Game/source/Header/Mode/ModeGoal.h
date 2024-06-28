//----------------------------------------------------------------------
// @filename ModeGoal.h
// @author: saito ko
// @explanation
// �S�[�����̉��o���s���N���X
//----------------------------------------------------------------------
#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
#include "../../Header/UI/Base/UIRotaBase.h"
#include <array>
class ModeGoal : public ModeBase
{
	public:
	ModeGoal(const std::string& name);
	~ModeGoal();
	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;

	void LoadUI();
	void AnimationProcess();
protected:
	class SuperManager* _superManager; // �X�[�p�[�}�l�[�W���[�N���X
	class Score* _score;// �_���N���X
	std::vector<UIRotaBase*> _ui; // UI�N���X
	std::array<int,10> _numHandle; // �����̃n���h��
	std::string _name; // ���_����ꂽ�����̖��O
	int _nowScore[2]; // ���݂̃X�R�A
	int _currentTime; // ���݂̎���
};

