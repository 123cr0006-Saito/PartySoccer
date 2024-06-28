//----------------------------------------------------------------------
// @filename Camera.cpp
// @author: saito ko
// @explanation
// プレイヤーの中心にカメラを追従させるクラス
//----------------------------------------------------------------------
#include "../../../Header/Other/Camera/Camera.h"
#include "../.../../AppFrame/source/System/Header/Function/Timer.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/PlayerManager.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
#include "../../../Header/Object/Player/Player.h"
Camera* Camera::_instance = nullptr;
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
Camera::Camera() :
	_isGame(false)
{
	if (_instance != nullptr) {
		DebugError();
		return;
	}
	_instance = this;
	_player = dynamic_cast<PlayerManager*>(SuperManager::GetInstance()->GetManager("playerManager"));
	
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Camera::~Camera(){
	_instance = nullptr;
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Camera::Update(){
	if(_isGame){
		UpdateGame();
	}	
	else{
		UpdateSelectAndResult();
	}
	return true;
};
//----------------------------------------------------------------------
// @brief 選択画面とリザルト画面のカメラの更新処理
// @return 無し
//----------------------------------------------------------------------
void Camera::UpdateSelectAndResult(){
	SetCameraPositionAndTarget_UpVecY(_pos.first.toVECTOR(), _pos.second.toVECTOR());
};
//----------------------------------------------------------------------
// @brief メインゲームのカメラの更新処理
// @return 無し
//----------------------------------------------------------------------
void Camera::UpdateGame(){

	if(_player == nullptr){
		DebugError();
	}

	std::vector<Player*> player = _player->GetList();

	Vector3D pos;
	for (int i = 0; i < player.size(); i++) {
		pos += player[i]->GetPos();
	}

	Vector3D targetPos = pos / player.size();
	Vector3D cameraPos = targetPos + Vector3D(0, 7000, -6000); // ターゲットから離したい距離分を足す

	double elapsedTime = Timer::GetInstance()->TimeElapsed();
    SpringDamperSystem(_pos.first,cameraPos, _cameraSpeed,elapsedTime);
	SpringDamperSystem(_pos.second,targetPos,_targetSpeed, elapsedTime);

	SetCameraPositionAndTarget_UpVecY(_pos.first.toVECTOR(), _pos.second.toVECTOR());
};
//----------------------------------------------------------------------
// @brief カメラの追従システム
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Camera::SpringDamperSystem(Vector3D& nowPos,const Vector3D& targetPos, Vector3D& speed,const double time){
	float springConstant = 100.0f;
	float dampingConstant = 20.0f;

	Vector3D pos = nowPos - targetPos;
	Vector3D springForce = pos * -springConstant; // バネの力 -kx 弾性力
	Vector3D dampingForce = speed * -dampingConstant; // ダンパの力 -cv 抵抗力
	Vector3D force = springForce + dampingForce; // 合力

	speed += force * time;
	nowPos += speed * time;

	return true;
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Camera::Draw(){
	printfDx("x:%f y:%f z:%f\n",_pos.first.x, _pos.first.y, _pos.first.z);
	printfDx("x:%f y:%f z:%f\n", _pos.second.x, _pos.second.y, _pos.second.z);
	printfDx("x:%f y:%f z:%f\n", _cameraSpeed.x, _cameraSpeed.y, _cameraSpeed.z);
	printfDx("x:%f y:%f z:%f\n", _targetSpeed.x, _targetSpeed.y, _targetSpeed.z);
	return true;
};
