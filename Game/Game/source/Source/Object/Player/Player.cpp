#include "../../../Header/Object/Player/Player.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../../../AppFrame/MemoryLeak.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Model/RimLightModel.h"
#include "../AppFrame/source/System/Header/Input/XInput.h"
Player::Player(std::string name, XInput* input, int handle) : ObjectBase(name) {
	_Input = input;
	int modelHandle = handle;
	_model = NEW RimLightModel(name, modelHandle);
	_model->SetPos(_pos);
	_forwardVec = Vector3D(0.0f, 0.0f, -1.0f);

	RenderManager* renderManager = dynamic_cast<RenderManager*>(SuperManager::GetInstance()->GetManager("renderManager"));
	renderManager->Add(10, _model);

	_capsule = NEW Capsule();
	_capsule->SetName("player");
	_capsule->up = 500.0f;
	_capsule->r = 170.0f;
	CollisionManager::GetInstance()->Add(this, _capsule);

	_stamina = 100;
	_isTired = false;
	_isShoot = false;
	_dash = 0;
	_power = 0;
	_glavity = 0.0f;

	// �A�j���[�V�����̐ݒ�
	std::string animationPath = "Res/Model/Player/Animation/" + _name + "_Walk.mv1";
	int animHandle = MV1LoadModel(animationPath.c_str());;
	_animIndex = MV1AttachAnim(modelHandle, 0, animHandle, FALSE);
	_totalTime = MV1GetAttachAnimTotalTime(modelHandle,_animIndex);
	_playTime = 0;
	_animBlendRate = 0;
};

Player::~Player(){
	delete _Input;
};

bool Player::Init(){
	return true;
};

bool Player::Update(){
	// ���̐ݒ�
	auto SetSphere = [&](Sphere* sphere) {
		sphere->pos = _pos +Vector3D(0,_capsule->up/2,0) + (_forwardVec * 350);
		sphere->r = 100.0f;
		sphere->name = "shoot";
	};
	// �p�����[�^�̉��Z
	auto AddParam = [](int* param,int max,int value){
		if ((*param) < max) (*param)+=value;
	};
	// �p�����[�^�̌��Z
	auto SubParam = [](int* param, int min, int value) {
		if ((*param) > min) (*param)-=value;
	};

	float speed = 50.0f;
	// �X�e�B�b�N�̓��͂��擾
	_Input->Input();
	auto inputStick = _Input->GetAdjustedStick_L();

	// �m�b�N�o�b�N�������I�����Ă���ꍇ�͏�����-------------------------------------
	if (_isKnockBack) {
		_pos += _knockBackVec * _knockBack;
		SubParam(&_knockBack, 0, 5);
		if(_knockBack <= 0){
			_knockBack = 0;
			_isKnockBack = false;
		}
		return true;
	}
	//-----------------------------------------------------------------------------------------------

	// �V���[�g�������I�����Ă���ꍇ�͏�����-------------------------------------
	if (_isShoot) {
		CollisionManager::GetInstance()->Del("shoot");
		_isShoot = false;
		_model->SetIsShader(false);
		_power = 0;
		_dash = 0;
	}
	//-----------------------------------------------------------------------------------------------
	
	// �ړ�����-------------------------------------
	// �ړ��������v�Z
	Vector3D moveDir(inputStick.x,0,inputStick.y);
	// ���K��
	Vector3D normalDir = moveDir.Normalize();
	// �ړ��l�Ƃ��ĉ��Z
	_pos += normalDir * (speed + _dash);
	// -------------------------------------------------

	// ��]����------------------------------------------------------------------------------------
	if(normalDir.Len()){
		float angle = Math::CalcVectorAngle(_forwardVec.toVECTOR(), normalDir.toVECTOR());
		float rotRad = 20.0f * DX_PI_F / 180.0f; // ��]���20�x
		if (rotRad > angle) {
			// �p�x����]����𒴂��Ă��Ȃ��ꍇ�͂��̂܂ܑ��
			_forwardVec = normalDir;
		}
		else {
			// �p�x����]����𒴂��Ă���ꍇ�͉�]�������s��
			Vector3D vN = _forwardVec.Cross(normalDir);
			_forwardVec = VTransform(_forwardVec.toVECTOR(), MGetRotAxis(vN.toVECTOR(), rotRad));
		}
	}
	//--------------------------------------------------------------------------------------------------

	//shoot�̐ݒ�-------------------------------------------------------------------------------------
	if (_Input->GetKey(XINPUT_BUTTON_B)) {
		// �p���[��50�����̏ꍇ�͑���
		AddParam(&_power, 50, 1);
		SubParam(&_dash,-25,1);
	}

	if (_Input->GetRel(XINPUT_BUTTON_B)) {
		// �V���[�g����
		Sphere* sphere = NEW Sphere();
		SetSphere(sphere);
		CollisionManager* collisionManager = dynamic_cast<CollisionManager*>(SuperManager::GetInstance()->GetManager("collisionManager"));
		CollisionManager::GetInstance()->Add(this, sphere);
		_isShoot = true;
	}
	//--------------------------------------------------------------------------------------------------

	// dash�̐ݒ�-------------------------------------------------------------------------------------
	if (_Input->GetKey(XINPUT_BUTTON_A) && !_isTired) {
		// �X�^�~�i��0�ȏ�̏ꍇ�͌���
		SubParam(&_stamina, 0, 1);
		AddParam(&_dash, 25, 1);
		if (_stamina == 0) {
			_isTired = true;
		}
	}
	else {
		// �X�^�~�i��100�����̏ꍇ�͑���
		AddParam(&_stamina, 100, 1);
		SubParam(&_dash, 0, 1);
		if (_stamina >= 100) {
			_isTired = false;
		}
	}
	//--------------------------------------------------------------------------------------------------

	// �A�j���[�V�����̐ݒ�
	AnimationUpdate(normalDir);
	
	_glavity += 3;
	_pos.y -= _glavity;

	if (_pos.y < 0.0f) {
		_pos.y = 0.0f;
		_glavity = 0.0f;
	}
	
	return true;
};

void Player::AnimationUpdate(const Vector3D& moveDir){
	_playTime += 1.0f;
	if (_playTime >= _totalTime) {
		_playTime = 0;
	}

	// �A�j���[�V�����̃u�����h
	if (moveDir.Sqlen()) {
		if (_animBlendRate < 1.0f) _animBlendRate += 0.1f;
	}
	else {
		if (_animBlendRate > 0.0f) _animBlendRate -= 0.1f;
	}

	if(_power == 25){
		_model->SetIsShader(true);
		_model->SetRimColor(0.0f,0.0f,1.0f);
	}
	else if(_power == 49){
		_model->SetIsShader(true);
		_model->SetRimColor(1.0f,0.0f,0.0f);
	}
	

	// �A�j���[�V�����̐ݒ�
	_model->SetAttachAnimBlendRate(_animIndex, _animBlendRate);
	_model->SetAttachAnimTime(_animIndex, _playTime);
};

bool Player::UpdateEnd() {
	// �ݒ�-------------------------------------------------------------------------------------------
	// �J�v�Z���̐ݒ�
	_capsule->pos = _pos;
	_capsule->Update();
	// ���f���̐ݒ�

	_model->SetModelForwardRotationY(_forwardVec);
	_model->SetPos(_pos);
	//-------------------------------------------------------------------------------------------------
	return true;
};

void Player::SetKnockBack(int knockBack, Vector3D knockBackVec){
	_knockBack = knockBack;
	_knockBackVec = knockBackVec.Normalize();_knockBackVec.y *= -1;
	_isKnockBack = true;
};

bool Player::DebugDraw(){
	printfDx("\n\n\nstamina : %d\ndash : %d\npower : %d",_stamina,_dash,_power);
	DrawSphere3D((_pos + Vector3D(0, _capsule->up / 2, 0) + (_forwardVec * 350)).toVECTOR(), 50.0f, 12, GetColor(255, 0, 0), GetColor(0, 0, 0), false);
	return true;
}