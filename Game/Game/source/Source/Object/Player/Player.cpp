#include "../../../Header/Object/Player/Player.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../../../AppFrame/MemoryLeak.h"
Player::Player(std::string name, std::pair<XInput*, int> param) : ObjectBase(name) {
	_Input = param.first;
	_modelHandle = param.second;
	_forwardVec = Vector3D(0.0f, 0.0f, -1.0f);
	RenderManager::GetInstance()->Add(name,10,_modelHandle);
	MV1SetScale(_modelHandle, VScale(VGet(1.0f,1.0f,1.0f),30.0f));

	_capsule = NEW Capsule();
	_capsule->SetName("player");
	_capsule->up = 500.0f;
	_capsule->r = 170.0f;
	CollisionManager::GetInstance()->Add(this, _capsule);

	_stamina = 100;
	_isTired = false;
	_dash = 0;
	_power = 0;
	_glavity = 0.0f;
};

Player::~Player(){
	MV1DeleteModel(_modelHandle);
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

	static bool isShoot = false;
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
	}
	//-----------------------------------------------------------------------------------------------

	// �V���[�g�������I�����Ă���ꍇ�͏�����-------------------------------------
	if (isShoot) {
		CollisionManager::GetInstance()->Del("shoot");
		isShoot = false;
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
		CollisionManager::GetInstance()->Add(this, sphere);
		isShoot = true;
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

	_glavity += 3;
	_pos.y -= _glavity;

	if (_pos.y < 0.0f) {
		_pos.y = 0.0f;
		_glavity = 0.0f;
	}


	// �ݒ�-------------------------------------------------------------------------------------------
	// �J�v�Z���̐ݒ�
	_capsule->pos = _pos;
	_capsule->Update();
	// ���f���̐ݒ�
	Math::SetModelForward_RotationY(_modelHandle, _forwardVec.toVECTOR());
	MV1SetPosition(_modelHandle, _pos.toVECTOR());
	//--------------------------------------------------------------------------------------------------

	return true;
};

void Player::SetKnockBack(int knockBack, Vector3D knockBackVec){
	_knockBack = knockBack;
	_knockBackVec = knockBackVec.Normalize();_knockBackVec.y *= -1;
	_isKnockBack = true;
};

bool Player::DebugDraw(){
	printfDx("\n\n\nstamina : %d\ndash : %d\npower : %d",_stamina,_dash,_power);
	DrawCapsule3D(_capsule->pos.toVECTOR(), _capsule->up_pos.toVECTOR(), _capsule->r, 12,GetColor(255, 0, 0), GetColor(0, 0, 0), false);
	DrawSphere3D((_pos + Vector3D(0, _capsule->up / 2, 0) + (_forwardVec * 350)).toVECTOR(), 50.0f, 12, GetColor(255, 0, 0), GetColor(0, 0, 0), false);
	return true;
}