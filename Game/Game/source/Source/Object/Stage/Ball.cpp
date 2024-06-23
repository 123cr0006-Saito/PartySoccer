#include "../../../Header/Object/Stage/Ball.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../AppFrame/MemoryLeak.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../AppFrame/source/System/Header/Resource/ResourceServer.h"
#include "../../../Header/Model/Base/ModelBase.h"
Ball::Ball(std::string name) : ObjectBase(name){
	int handle = ResourceServer::MV1LoadModel("Ball", "Res/Model/Ball/SoccerBall.mv1");
	_model = NEW ModelBase(name, handle);
	_model->SetScale(Vector3D(10,10,10));
	_model->SetPos(_pos);

	_sphere = NEW Sphere();
	_pos = Vector3D(0.0f, 350.0f, 0.0f);
	_sphere->pos = _pos;
	_sphere->SetName("ball");
	_sphere->r = 500.0f;
	_isShoot= false;
	_speed = 0.0f;
	_dirVec = Vector3D(0.0f, 0.0f, 0.0f);
	_glavity = 0.0f;
	_oldPos = _pos;
	 RenderManager* renderManager = dynamic_cast<RenderManager*>(SuperManager::GetInstance()->GetManager("renderManager"));
	 renderManager->Add(10, _model);
	 CollisionManager::GetInstance()->Add(this, _sphere);
};

Ball::~Ball(){

};

bool Ball::Init(){
	return true;
};

bool Ball::Update() {
	_oldPos = _pos;
	// ãÖÇÃê›íË
	auto AddParam = [](float* param, float max, float value) {
		if ((*param) < max) (*param) += value;
		else if ((*param) > max) (*param) = max;
	};
	auto SubParam = [](float* param, float min, float value) {
		if ((*param) > min) (*param) -= value;
		else if((*param) < 0) (*param) = 0;
	};

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

	return true;
};

bool Ball::UpdateEnd() {
	_model->SetRotation(_dirVec);
	_model->SetPos(_pos);
	return true;
}

bool Ball::DebugDraw(){
	return true;
};

void Ball::SetForwardVec(Vector3D forwardVec) {
	_forwardVec = forwardVec.Normalize(); 
	float angle = atan2f(_forwardVec.x, _forwardVec.z);
	_dirVec = Vector3D(_dirVec.x, angle, 0.0f);
}