#include "../../../Header/Object/Player/Player.h"
#include "../../../Header/Manager/RenderManager.h"
Player::Player(std::string name, std::pair<XInput*, int> param) : ObjectBase(name) {
	_Input = param.first;
	_modelHandle = param.second;
	_forwardVec = Vector3D(0.0f, 0.0f, -1.0f);
	RenderManager::GetInstance()->Add(name,10,_modelHandle);
};

Player::~Player(){
	
};

bool Player::Init(){
	return true;
};

bool Player::Update(){
	float speed = 10.0f;
	// �X�e�B�b�N�̓��͂��擾
	_Input->Input();
	auto inputStick = _Input->GetAdjustedStick_L();

	// �ړ�����-------------------------------------
	// �ړ��������v�Z
	Vector3D moveDir(inputStick.x,0,inputStick.y);
	// ���K��
	Vector3D normalDir = moveDir.Normalize();
	// �ړ��l�Ƃ��ĉ��Z
	_pos += normalDir * speed;
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

	// �ݒ�-------------------------------------------------------------------------------------------
	Math::SetModelForward_RotationY(_modelHandle, _forwardVec.toVECTOR());
	MV1SetPosition(_modelHandle, _pos.toVECTOR());
	//--------------------------------------------------------------------------------------------------

	SetCameraPositionAndTarget_UpVecY((_pos + Vector3D(0,200,-250)).toVECTOR(), _pos.toVECTOR());
	return true;
};
