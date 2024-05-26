#include "../../../Header/Object/Player/Player.h"
Player::Player(std::string name, std::pair<XInput*, int> param) : ObjectBase() {
	_name = name;
	_Input = param.first;
	_modelHandle = param.second;
};

Player::~Player(){

};

bool Player::Init(){
	return true;
};

bool Player::Update(){
	return true;
};
