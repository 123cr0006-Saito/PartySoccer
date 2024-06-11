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
	// スティックの入力を取得
	_Input->Input();
	auto inputStick = _Input->GetAdjustedStick_L();

	// 移動処理-------------------------------------
	// 移動方向を計算
	Vector3D moveDir(inputStick.x,0,inputStick.y);
	// 正規化
	Vector3D normalDir = moveDir.Normalize();
	// 移動値として加算
	_pos += normalDir * speed;
	// -------------------------------------------------

	// 回転処理------------------------------------------------------------------------------------
	if(normalDir.Len()){
		float angle = Math::CalcVectorAngle(_forwardVec.toVECTOR(), normalDir.toVECTOR());
		float rotRad = 20.0f * DX_PI_F / 180.0f; // 回転上限20度
		if (rotRad > angle) {
			// 角度が回転上限を超えていない場合はそのまま代入
			_forwardVec = normalDir;
		}
		else {
			// 角度が回転上限を超えている場合は回転処理を行う
			Vector3D vN = _forwardVec.Cross(normalDir);
			_forwardVec = VTransform(_forwardVec.toVECTOR(), MGetRotAxis(vN.toVECTOR(), rotRad));
		}
	}
	//--------------------------------------------------------------------------------------------------

	//shootの設定-------------------------------------------------------------------------------------
	if (_Input->GetKey(XINPUT_BUTTON_B)) {
		// パワーが50未満の場合は増加
		if (_power < 50) {
			_power++;
		}
	}

	if (_Input->GetRel(XINPUT_BUTTON_B)) {
		// パワーが50以上の場合はシュート
		// シュート処理
		_power = 0;
	}
	//--------------------------------------------------------------------------------------------------

	// 設定-------------------------------------------------------------------------------------------
	_capsule->pos = _pos;
	Math::SetModelForward_RotationY(_modelHandle, _forwardVec.toVECTOR());
	MV1SetPosition(_modelHandle, _pos.toVECTOR());
	//--------------------------------------------------------------------------------------------------

	return true;
};
