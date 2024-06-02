#include "../../../Header/Object/Stage/Ball.h"

Ball::Ball(std::string name) : ObjectBase(name){
	_modelHandle = MV1LoadModel("Res/Model/Ball/SoccerBall.mv1");
};

Ball::~Ball(){

};

bool Ball::Init(){
	return true;
};

bool Ball::Update() {
	return true;
};