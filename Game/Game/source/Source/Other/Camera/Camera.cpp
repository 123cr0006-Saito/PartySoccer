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
	_isGame(false),
	_currentTime(GetNowCount())
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
	_pos.first = targetPos + Vector3D(0, 3500, -3000) *2;

	SpringDamperSystem(targetPos);

	SetCameraPositionAndTarget_UpVecY(_pos.first.toVECTOR(), (_pos.second + (targetPos - _pos.second) / 1.3f).toVECTOR());
};
//----------------------------------------------------------------------
// @brief メインゲームかどうかを設定
// @param メインゲームかどうか
// @return 無し
//----------------------------------------------------------------------
void Camera::SetIsGame(bool isGame) {
	_isGame = isGame; 
	_holdPos.first = _pos.first;
	_holdPos.second = _pos.second;
	_currentTime = GetNowCount();
};
//----------------------------------------------------------------------
// @brief カメラの追従システム
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Camera::SpringDamperSystem(Vector3D targetPos){
	float springConstant = 100.0f;
	float dampingConstant = 20.0f;
	double elapsedTime = Timer::GetInstance()->TimeElapsed();

	Vector3D pos = _pos.second - targetPos;
	Vector3D springForce = pos * -springConstant; // バネの力 -kx 弾性力
	Vector3D dampingForce = _speed * -dampingConstant; // ダンパの力 -cv 抵抗力
	Vector3D force = springForce + dampingForce; // 合力

	_speed += force * elapsedTime;
	_pos.second += _speed * elapsedTime;

	return true;
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Camera::Draw(){
	printfDx("x:%f y:%f z:%f\n",_pos.first.x, _pos.first.y, _pos.first.z);
	printfDx("x:%f y:%f z:%f\n", _pos.second.x, _pos.second.y, _pos.second.z);
	return true;
};
