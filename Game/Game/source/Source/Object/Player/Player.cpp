//----------------------------------------------------------------------
// @filename Player.cpp
// @author: saito ko
// @explanation
// プレイヤークラス
//----------------------------------------------------------------------
#include "../../../Header/Object/Player/Player.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Model/RimLightModel.h"
#include "../AppFrame/source/Application/Global.h"
#include "../AppFrame/MemoryLeak.h"
#include "../AppFrame/source/System/Header/Input/XInput.h"
//----------------------------------------------------------------------
// @brief 定数宣言
//----------------------------------------------------------------------
namespace{
	constexpr auto POWER_MAX = 50;
	constexpr auto DASH_MAX = 25;
	constexpr auto STAMINA_MAX = 100;
}
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param 名前
// @param パッドクラス
// @param モデルハンドル
// @return 無し
//----------------------------------------------------------------------
Player::Player(const std::string& name,XInput* input,const int handle) : ObjectBase(name) {
	_Input = input;
	int modelHandle = handle;
	_model = NEW RimLightModel(name,10, modelHandle);
	_model->SetPos(_pos);
	_forwardVec = Vector3D(0.0f, 0.0f, -1.0f);

	SuperManager::GetInstance()->GetManager("renderManager")->Add(_model);
	_capsule = NEW Capsule("player",_pos,600.0f,170.0f,this);
	SuperManager::GetInstance()->GetManager("collisionManager")->Add(_capsule);

	_stamina = 100;
	_knockBack = 0;
	_dash = 0;
	_power = 0;
	_glavity = 0;

	_isTired = false;
	_isShoot = false;
	_isPowerMax = false;
	_isKnockBack = false;
	_isGame = true;

	// アニメーションの設定
	std::string animationPath = "Res/Model/Player/Animation/" + _name + "_Walk.mv1";
	int animHandle = MV1LoadModel(animationPath.c_str());;
	_animIndex = MV1AttachAnim(modelHandle, 0, animHandle, FALSE);
	_totalTime = MV1GetAttachAnimTotalTime(modelHandle,_animIndex);
	_playTime = 0;
	_animBlendRate = 0;
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Player::~Player(){
	delete _Input;
	SuperManager::GetInstance()->GetManager("collisionManager")->Delete(_capsule);
	SuperManager::GetInstance()->GetManager("renderManager")->Delete(_model);
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Player::Update(){
	_Input->Input();
	 UpdateGame();
	return true;
};
//----------------------------------------------------------------------
// @brief メインゲームでの更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Player::UpdateGame(){
	// パラメータの減算
	auto SubParam = [](int* param, int min, int value) {
		if ((*param) > min) (*param) -= value;
	};

	// スティックの入力を取得

	auto inputStick = _Input->GetAdjustedStick_L();

	// 移動方向を計算
	Vector3D moveDir(inputStick.x, 0, inputStick.y);
	// 正規化
	Vector3D normalDir = moveDir.Normalize();

	// ノックバック処理が終了している場合は初期化--------------------------------
	if (_isKnockBack) {
		_pos += _knockBackVec * _knockBack;
		SubParam(&_knockBack, 0, 5);
		if (_knockBack <= 0) {
			_knockBack = 0;
			_isKnockBack = false;
		}
	}
	//-----------------------------------------------------------------------------------------------

	// シュート処理が終了している場合は初期化-------------------------------------
	if (_isShoot) {
		SuperManager::GetInstance()->GetManager("collisionManager")->DeleteName("shoot");
		_isShoot = false;
		_isPowerMax = false;
		_model->SetIsShader(false);
		_power = 0;
		_dash = 0;
	}
	//-----------------------------------------------------------------------------------------------

	// 移動処理
	MoveUpdate(normalDir);
	// シュート処理
	ShootUpdate();
	// ダッシュ処理
	DashUpdate();
	// 重力処理
	GravityUpdate();
	// アニメーションの設定
	AnimationUpdate(normalDir);
	return true;
};
//----------------------------------------------------------------------
// @brief 移動処理
// @param 移動方向
// @return 無し
//----------------------------------------------------------------------
void Player::MoveUpdate(const Vector3D& normalDir){
	float speed = 50.0f;
	// 移動値として加算
	_pos += normalDir * (speed + _dash);

	// 回転処理
	if (normalDir.Len()) {
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
};
//----------------------------------------------------------------------
// @brief シュート処理
// @return 無し
//----------------------------------------------------------------------
void Player::ShootUpdate(){
	// パラメータの加算
	auto AddParam = [](int* param, int max, int value) {
		if ((*param) < max) (*param) += value;
	};
	// パラメータの減算
	auto SubParam = [](int* param, int min, int value) {
		if ((*param) > min) (*param) -= value;
	};

	if (_Input->GetKey(XINPUT_BUTTON_B)) {
		// パワーが50未満の場合は増加
		AddParam(&_power, POWER_MAX, 1);
		SubParam(&_dash, -DASH_MAX, 1);
	}

	if (_Input->GetRel(XINPUT_BUTTON_B)) {
		// シュート処理
		Sphere* sphere = NEW Sphere("shoot", _pos + Vector3D(0, _capsule->up / 2, 0) + (_forwardVec * 350),100,this);
		SuperManager::GetInstance()->GetManager("collisionManager")->Add(sphere);
		_isShoot = true;
	}
};
//----------------------------------------------------------------------
// @brief ダッシュ処理
// @return 無し
//----------------------------------------------------------------------
void Player::DashUpdate(){
	// パラメータの加算
	auto AddParam = [](int* param, int max, int value) {
		if ((*param) < max) (*param) += value;
	};
	// パラメータの減算
	auto SubParam = [](int* param, int min, int value) {
		if ((*param) > min) (*param) -= value;
	};

	if (!_isTired && _Input->GetKey(XINPUT_BUTTON_A)) {
		// スタミナが0以上の場合は減少
		SubParam(&_stamina, 0, 1);
		AddParam(&_dash, DASH_MAX, 1);
		if (_stamina == 0) {
			_isTired = true;
		}
	}
	else {
		// スタミナが100未満の場合は増加
		AddParam(&_stamina, STAMINA_MAX, 1);
		SubParam(&_dash, 0, 1);
		if (_stamina >= 100) {
			_isTired = false;
		}
	}
};
//----------------------------------------------------------------------
// @brief 重力処理
// @return 無し
//----------------------------------------------------------------------
void Player::GravityUpdate(){
	_glavity += 3;
	_pos.y -= _glavity;

	if (_pos.y < 0.0f) {
		_pos.y = 0.0f;
		_glavity = 0.0f;
	}
};
//----------------------------------------------------------------------
// @brief アニメーションの更新処理
// @param 移動方向
// @return 無し
//----------------------------------------------------------------------
void Player::AnimationUpdate(const Vector3D& moveDir){

	_playTime += 1.0f;
	if (_playTime >= _totalTime) {
		_playTime = 0;
	}

	// アニメーションのブレンド
	if (moveDir.Sqlen()) {
		if (_animBlendRate < 1.0f) _animBlendRate += 0.1f;
	}
	else {
		if (_animBlendRate > 0.0f) _animBlendRate -= 0.1f;
	}

	if(_power == POWER_MAX / 2){
		_model->SetIsShader(true);
		_model->SetRimColor(0.0f,0.0f,1.0f);
		global._soundServer->DirectPlay("SE_GaugeHalf");
	}
	else if(!_isPowerMax && _power == POWER_MAX){
		_isPowerMax = true;
		_model->SetIsShader(true);
		_model->SetRimColor(1.0f,0.0f,0.0f);
		global._soundServer->DirectPlay("SE_GaugeMax");
	}
	

	// アニメーションの設定
	_model->SetAttachAnimBlendRate(_animIndex, _animBlendRate);
	_model->SetAttachAnimTime(_animIndex, _playTime);
};
//----------------------------------------------------------------------
// @brief モデルとコリジョンの位置を更新
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Player::UpdateEnd() {
	// カプセルの設定
	_capsule->pos = _pos;
	_capsule->Update();
	// モデルの設定
	_model->SetModelForwardRotationY(_forwardVec);
	_model->SetPos(_pos);
	return true;
};
//----------------------------------------------------------------------
// @brief ノックバックの強さと方向を設定
// @param ノックバックの強さ
// @param ノックバックの方向
// @return 成功したかどうか
//----------------------------------------------------------------------
void Player::SetKnockBack(const int knockBack,const Vector3D& knockBackVec){
	_knockBack = knockBack;
	_knockBackVec = knockBackVec.Normalize();
	_isKnockBack = true;
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Player::DebugDraw(){
	printfDx("\n\n\nstamina : %d\ndash : %d\npower : %d",_stamina,_dash,_power);
	DrawSphere3D((_pos + Vector3D(0, _capsule->up / 2, 0) + (_forwardVec * 350)).toVECTOR(), 50.0f, 12, GetColor(255, 0, 0), GetColor(0, 0, 0), false);
	return true;
}