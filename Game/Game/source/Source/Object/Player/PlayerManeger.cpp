#include "../../../Header/Object/Player/PlayerManeger.h"
#include "../MemoryLeak.h"

PlayerManeger* PlayerManeger::_instance = nullptr;

PlayerManeger::PlayerManeger(){
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
