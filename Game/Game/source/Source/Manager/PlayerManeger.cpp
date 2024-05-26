#include "../../Header/Manager/PlayerManeger.h"
#include "../MemoryLeak.h"

PlayerManeger* PlayerManeger::_instance = nullptr;

PlayerManeger::PlayerManeger() : ManagerBase(){
	_instance = this;
};

PlayerManeger::~PlayerManeger(){

};

bool PlayerManeger::Update(){
	return true;
};

bool PlayerManeger::CreatePlayer(std::vector<std::pair<XInput*, int>> param) {
	for (int i = 0; i < param.size(); i++) {
		_player.push_back(NEW Player(param[i]));
	}
	return true;
};

bool PlayerManeger::Draw(){
	return true;
}