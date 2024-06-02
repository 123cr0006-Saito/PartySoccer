#include "../../../Header/Other/Camera/Camera.h"
#include "../.../../AppFrame/source/System/Header/Function/Timer.h"
Camera::Camera(){
	_player = PlayerManeger::GetInstance();
};

Camera::~Camera(){

};

bool Camera::Update(){
	std::vector<std::pair<std::string, Player*>> player = _player->GetList();

	Vector3D pos;
	for(int i = 0; i < player.size(); i++){
		pos += player[i].second->GetPos();
	}

	_pos.second = pos / player.size();
	SpringDamperSystem(_pos.second + Vector3D(0, 3500, -3000));

	SetCameraPositionAndTarget_UpVecY(_pos.first.toVECTOR(), _pos.second.toVECTOR());
	return true;
};

bool Camera::SpringDamperSystem(Vector3D targetPos){
	float springConstant = 25.0f;
	float dampingConstant = 10.0f;
	double elapsedTime = Timer::GetInstance()->TimeElapsed();

	Vector3D pos = _pos.first - targetPos;
	Vector3D springForce = pos * -springConstant;
	Vector3D dampingForce = _speed * -dampingConstant;
	Vector3D force = springForce + dampingForce;

	_speed += force * elapsedTime;
	_pos.first += _speed * elapsedTime;
	
	bool isSlide = true;
	if(isSlide){
	    _pos.first.z = _pos.second.z -3000;
    }

	return true;
};

bool Camera::Draw(){
	printfDx("x:%f y:%f z:%f\n",_pos.first.x, _pos.first.y, _pos.first.z);
	printfDx("x:%f y:%f z:%f\n", _pos.second.x, _pos.second.y, _pos.second.z);
	return true;
};
