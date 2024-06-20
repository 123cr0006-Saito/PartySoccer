#pragma once
#include "../Base/ObjectBase.h"
#include "../../../AppFrame/source/System/Header/Input/XInput.h"
#include <string>
#include <utility>
#include <algorithm>
class Player : public ObjectBase
{
public:
	Player(std::tuple<std::string,XInput*,int> param);
	~Player();
	virtual bool Init() override;
	virtual bool Update()override;
	virtual bool UpdateEnd()override;
	void AnimationUpdate();
	virtual bool DebugDraw()override;

	void SetKnockBack(int knockBack, Vector3D knockBackVec);
	const bool GetIsKnockBack() { return _isKnockBack; }
	const int GetPower() { return _power; }
	const int GetStamina() { return _stamina; }
	const int GetDash() { return _dash; }
	const Vector3D GetForwardVec() { return _forwardVec; }
	XInput* GetInput() { return _Input; }
protected:
	XInput* _Input; // ����
	int _dash; // �_�b�V�����̃X�s�[�h
	int _stamina; // �v���C���[�̃X�^�~�i
	bool _isTired; // ���Ă��邩�ǂ���
	int _power;	// �v���C���[�̍U����
	int _glavity; // �d��
	Vector3D _forwardVec; // �O�����̃x�N�g��
	Capsule* _capsule; // �����蔻��

	bool _isKnockBack; // �m�b�N�o�b�N�����ǂ���
	int _knockBack; // �m�b�N�o�b�N�̋���
	Vector3D _knockBackVec; // �m�b�N�o�b�N�̕���

	//�A�j���[�V����
	int _animIndex;// �A�j���[�V�����n���h��
	float _totalTime;// �A�j���[�V�����̑��Đ�����
	float _playTime;// �A�j���[�V�����̍Đ�����
	float _animBlendRate;// �A�j���[�V�����̃u�����h���[�g
};

