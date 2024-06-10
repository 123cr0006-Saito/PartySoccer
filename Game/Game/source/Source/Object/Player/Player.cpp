#include "../../../Header/Object/Player/Player.h"
#include "../../../Header/Manager/RenderManager.h"
Player::Player(std::string name, std::pair<XInput*, int> param) : ObjectBase(name) {
	_Input = param.first;
	_modelHandle = param.second;
	_forwardVec = Vector3D(0.0f, 0.0f, -1.0f);
	RenderManager::GetInstance()->Add(name,10,_modelHandle);
	MV1SetScale(_modelHandle, VScale(VGet(1.0f,1.0f,1.0f),30.0f));

	_capsule->SetName("player");
	_capsule->up = 150.0f;
	_capsule->r = 50.0f;
};

Player::~Player(){
	MV1DeleteModel(_modelHandle);
};

bool Player::Init(){
	return true;
};

bool Player::Update(){
	float speed = 50.0f;
	// ƒXƒeƒBƒbƒN‚Ì“ü—Í‚ðŽæ“¾
	_Input->Input();
	auto inputStick = _Input->GetAdjustedStick_L();

	// ˆÚ“®ˆ—-------------------------------------
	// ˆÚ“®•ûŒü‚ðŒvŽZ
	Vector3D moveDir(inputStick.x,0,inputStick.y);
	// ³‹K‰»
	Vector3D normalDir = moveDir.Normalize();
	// ˆÚ“®’l‚Æ‚µ‚Ä‰ÁŽZ
	_pos += normalDir * speed;
	// -------------------------------------------------

	// ‰ñ“]ˆ—------------------------------------------------------------------------------------
	if(normalDir.Len()){
		float angle = Math::CalcVectorAngle(_forwardVec.toVECTOR(), normalDir.toVECTOR());
		float rotRad = 20.0f * DX_PI_F / 180.0f; // ‰ñ“]ãŒÀ20“x
		if (rotRad > angle) {
			// Šp“x‚ª‰ñ“]ãŒÀ‚ð’´‚¦‚Ä‚¢‚È‚¢ê‡‚Í‚»‚Ì‚Ü‚Ü‘ã“ü
			_forwardVec = normalDir;
		}
		else {
			// Šp“x‚ª‰ñ“]ãŒÀ‚ð’´‚¦‚Ä‚¢‚éê‡‚Í‰ñ“]ˆ—‚ðs‚¤
			Vector3D vN = _forwardVec.Cross(normalDir);
			_forwardVec = VTransform(_forwardVec.toVECTOR(), MGetRotAxis(vN.toVECTOR(), rotRad));
		}
	}
	//--------------------------------------------------------------------------------------------------

	// Ý’è-------------------------------------------------------------------------------------------
	_capsule->pos = _pos;
	Math::SetModelForward_RotationY(_modelHandle, _forwardVec.toVECTOR());
	MV1SetPosition(_modelHandle, _pos.toVECTOR());
	//--------------------------------------------------------------------------------------------------

	return true;
};
