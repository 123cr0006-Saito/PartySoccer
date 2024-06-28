//----------------------------------------------------------------------
// @filename Ball.cpp
// @author: saito ko
// @explanation
// ボールクラス
//----------------------------------------------------------------------
#include "../../../Header/Object/Stage/Ball.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../AppFrame/MemoryLeak.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../AppFrame/source/System/Header/Resource/ResourceServer.h"
#include "../../../Header/Model/Base/ModelBase.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param オブジェクトの名前
// @return 無し
//----------------------------------------------------------------------
Ball::Ball(const std::string& name) : ObjectBase(name){

	_pos = Vector3D(0.0f, 350.0f, 0.0f);

	int handle = ResourceServer::MV1LoadModel("Ball", "Res/Model/Ball/SoccerBall.mv1");
	_model = NEW ModelBase(name, 10, handle);
	_model->SetScale(Vector3D(10,10,10));
	_model->SetPos(_pos);

	_sphere = NEW Sphere("ball",_pos,500.0f,this);
	_isShoot= false;
	_speed = 0.0f;
	_dirVec = Vector3D(0.0f, 0.0f, 0.0f);
	_gravity = 0.0f;
	_oldPos = _pos;
	 SuperManager::GetInstance()->GetManager("renderManager")->Add(_model);
	 SuperManager::GetInstance()->GetManager("collisionManager")->Add(_sphere);
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Ball::~Ball(){
	SuperManager::GetInstance()->GetManager("renderManager")->Delete(_model);
	SuperManager::GetInstance()->GetManager("collisionManager")->Delete(_sphere);
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Ball::Update() {
	_oldPos = _pos;
	// 球の設定
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

	_gravity += 5;
	_pos.y -= _gravity;

	if(_pos.y < 350.0f){
		_pos.y = 350.0f;
		_gravity = 0.0f;
	}

	_sphere->pos = _pos;
	SubParam(&_speed, 0.0f, 5.0f);

	return true;
};
//----------------------------------------------------------------------
// @brief 更新終了後に行う処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Ball::UpdateEnd() {
	_model->SetRotation(_dirVec);
	_model->SetPos(_pos);
	return true;
}
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool Ball::DebugDraw(){
	return true;
};
//----------------------------------------------------------------------
// @brief 正面方向を設定する
// @param 正面方向
// @return 成功したかどうか
//----------------------------------------------------------------------
void Ball::SetForwardVec(const Vector3D& forwardVec) {
	_forwardVec = forwardVec.Normalize(); 
	float angle = atan2f(_forwardVec.x, _forwardVec.z);
	_dirVec = Vector3D(_dirVec.x, angle, 0.0f);
}