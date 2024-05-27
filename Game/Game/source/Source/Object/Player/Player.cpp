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
	// ƒXƒeƒBƒbƒN‚Ì“ü—Í‚ğæ“¾
	_Input->Input();
	auto inputStick = _Input->GetAdjustedStick_L();

	// ˆÚ“®ˆ—-------------------------------------
	// ˆÚ“®•ûŒü‚ğŒvZ
	Vector3D moveDir(inputStick.x,0,inputStick.y);
	// ³‹K‰»
	Vector3D normalDir = moveDir.Normalize();
	// ˆÚ“®’l‚Æ‚µ‚Ä‰ÁZ
	_pos += normalDir * speed;
	// -------------------------------------------------

	// ‰ñ“]ˆ—------------------------------------------------------------------------------------
	if(normalDir.Len()){
		float angle = Math::CalcVectorAngle(_forwardVec.toVECTOR(), normalDir.toVECTOR());
		float rotRad = 20.0f * DX_PI_F / 180.0f; // ‰ñ“]ãŒÀ20“x
		if (rotRad > angle) {
			// Šp“x‚ª‰ñ“]ãŒÀ‚ğ’´‚¦‚Ä‚¢‚È‚¢ê‡‚Í‚»‚Ì‚Ü‚Ü‘ã“ü
			_forwardVec = normalDir;
		}
		else {
			// Šp“x‚ª‰ñ“]ãŒÀ‚ğ’´‚¦‚Ä‚¢‚éê‡‚Í‰ñ“]ˆ—‚ğs‚¤
			Vector3D vN = _forwardVec.Cross(normalDir);
			_forwardVec = VTransform(_forwardVec.toVECTOR(), MGetRotAxis(vN.toVECTOR(), rotRad));
		}
	}
	//--------------------------------------------------------------------------------------------------

	// İ’è-------------------------------------------------------------------------------------------
	Math::SetModelForward_RotationY(_modelHandle, _forwardVec.toVECTOR());
	MV1SetPosition(_modelHandle, _pos.toVECTOR());
	//--------------------------------------------------------------------------------------------------

	SetCameraPositionAndTarget_UpVecY((_pos + Vector3D(0,200,-250)).toVECTOR(), _pos.toVECTOR());
	return true;
};
