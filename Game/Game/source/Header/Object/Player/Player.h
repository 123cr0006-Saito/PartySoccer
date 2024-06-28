//----------------------------------------------------------------------
// @filename Player.h
// @author: saito ko
// @explanation
// �v���C���[�N���X
//----------------------------------------------------------------------
#pragma once
#include "../Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
#include <string>
#include <utility>
#include <algorithm>
class Player : public ObjectBase
{
public:
	Player(const std::string& name ,class XInput* input,const int handle);
	~Player();

	virtual bool Update()override;
	bool UpdateGame();
	virtual bool UpdateEnd()override;

	void MoveUpdate(const Vector3D& normalDir);
	void ShootUpdate();
	void DashUpdate();
	void GravityUpdate();
	void AnimationUpdate(const Vector3D& normalDir);

	virtual bool DebugDraw()override;

	void SetKnockBack(const int knockBack, const Vector3D& knockBackVec);
	void SetPower(const int power) { _power = power; }
	void SetStamina(const int stamina) { _stamina = stamina; }
	void SetIsGame(const bool isGame) { _isGame = isGame; }

	bool GetIsKnockBack() const { return _isKnockBack; }
	int GetPower() const { return _power; }
	int GetStamina() const { return _stamina; }
	int GetDash() const { return _dash; }
	Capsule* GetCapsule() const { return _capsule; }
protected:
	class XInput* _Input; // ����
	class RimLightModel* _model; // ���f��

	int _dash; // �_�b�V�����̃X�s�[�h
	int _stamina; // �v���C���[�̃X�^�~�i
	int _power;	// �v���C���[�̍U����
	int _glavity; // �d��

	bool _isTired; // ���Ă��邩�ǂ���
	bool _isShoot; // �V���[�g��ł������ǂ���
	bool _isPowerMax; // �p���[���ő傩�ǂ���
	bool _isGame;//���C���Q�[�����ǂ���

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

