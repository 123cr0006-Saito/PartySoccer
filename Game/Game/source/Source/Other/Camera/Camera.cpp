#include "../../../Header/Other/Camera/Camera.h"
#include "../.../../AppFrame/source/System/Header/Function/Timer.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/PlayerManeger.h"
Camera::Camera(){
	_player = dynamic_cast<PlayerManeger*>(SuperManager::GetInstance()->GetManager("playerManager"));
	//カメラの初期化
	SetupCamera_Perspective(60.0f * 180.0f / 3.141592f);
};

Camera::~Camera(){

};

bool Camera::Update(){
	std::vector<std::pair<std::string, Player*>> player = _player->GetList();

	Vector3D pos;
	for(int i = 0; i < player.size(); i++){
		pos += player[i].second->GetPos();
	}

	Vector3D targetPos = pos / player.size();
	_pos.first = targetPos + Vector3D(0, 3500, -3000)*2;
	SpringDamperSystem(targetPos);

	SetCameraPositionAndTarget_UpVecY(_pos.first.toVECTOR(), (_pos.second /*+ (targetPos - _pos.second)/1.3f*/).toVECTOR());
	return true;
};

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

bool Camera::Draw(){
	printfDx("x:%f y:%f z:%f\n",_pos.first.x, _pos.first.y, _pos.first.z);
	printfDx("x:%f y:%f z:%f\n", _pos.second.x, _pos.second.y, _pos.second.z);
	return true;
};
