#pragma once
#include "../Base/ObjectBase.h"
#include <string>
#include <utility>
#include <algorithm>
class Player : public ObjectBase
{
public:
	Player(std::string,class XInput*,int);
	~Player();
	virtual bool Init() override;
	virtual bool Update()override;
	virtual bool UpdateEnd()override;
	void AnimationUpdate(const Vector3D& moveDir);
	virtual bool DebugDraw()override;

	void SetKnockBack(int knockBack, Vector3D knockBackVec);
	void SetPower(int power) { _power = power; }
	void SetStamina(int stamina) { _stamina = stamina; }

	const bool GetIsKnockBack() { return _isKnockBack; }
	const int GetPower() { return _power; }
	const int GetStamina() { return _stamina; }
	const int GetDash() { return _dash; }
	const Vector3D GetForwardVec() { return _forwardVec; }
protected:

	class XInput* _Input; // ����
	class RimLightModel* _model; // ���f��

	int _dash; // �_�b�V�����̃X�s�[�h
	int _stamina; // �v���C���[�̃X�^�~�i
	bool _isTired; // ���Ă��邩�ǂ���
	bool _isShoot; // �V���[�g��ł������ǂ���
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

