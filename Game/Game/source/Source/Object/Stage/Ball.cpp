#include "../../../Header/Object/Stage/Ball.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../AppFrame/MemoryLeak.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
#include "../../../Header/Manager/PlayerManeger.h"
Ball::Ball(std::string name) : ObjectBase(name){
	_modelHandle = MV1LoadModel("Res/Model/Ball/SoccerBall.mv1");
	MV1SetScale(_modelHandle, VScale(VGet(1.0f, 1.0f, 1.0f), 10.0f));
	_sphere = NEW Sphere();
	_pos = Vector3D(0.0f, 350.0f, 0.0f);
	_sphere->pos = _pos;
	_sphere->name = "ball";
	_sphere->r = 500.0f;
	_isShoot= false;
	_speed = 0.0f;
	_dirVec = Vector3D(0.0f, 0.0f, 0.0f);
	_glavity = 0.0f;

	RenderManager::GetInstance()->Add(name, 10, _modelHandle);
	CollisionManager::GetInstance()->Add(this, _sphere);
};

Ball::~Ball(){

};

bool Ball::Init(){
	return true;
};

bool Ball::Update() {
	// ãÖÇÃê›íË
	auto AddParam = [](float* param, float max, float value) {
		if ((*param) < max) (*param) += value;
	};
	auto SubParam = [](float* param, float min, float value) {
		if ((*param) > min) (*param) -= value;
	};

	if (PlayerManeger::GetInstance()->GetList()[0].second->GetInput()->GetTrg(XINPUT_BUTTON_START)) {
		_pos = Vector3D(0, 0, 0);
	}

	_isShoot = _speed > 150 ? true : false;

	_dirVec.x += 0.002f * _speed;
	_pos += _forwardVec * _speed;

	_glavity += 5;
	_pos.y -= _glavity;

	if(_pos.y < 350.0f){
		_pos.y = 350.0f;
		_glavity = 0.0f;
	}

	_sphere->pos = _pos;
	SubParam(&_speed, 0.0f, 5.0f);

	MV1SetRotationXYZ(_modelHandle, _dirVec.toVECTOR());
	MV1SetPosition(_modelHandle, _pos.toVECTOR());
	return true;
};

bool Ball::DebugDraw(){
	DrawSphere3D(_sphere->pos.toVECTOR(), _sphere->r, 16, GetColor(0,255,0), GetColor(0, 255, 0), false);
	return true;
};

void Ball::SetForwardVec(Vector3D forwardVec) { 
	_forwardVec = forwardVec.Normalize(); 
	float angle = atan2f(_forwardVec.x, _forwardVec.z);
	_dirVec = Vector3D(_dirVec.x, angle, 0.0f);
}