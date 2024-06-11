#include "../../Header/Manager/PlayerManeger.h"
#include "../MemoryLeak.h"

PlayerManeger* PlayerManeger::_instance = nullptr;

PlayerManeger::PlayerManeger() {
	_instance = this;
};

PlayerManeger::~PlayerManeger(){

};

bool PlayerManeger::Update(){
	for (auto&& list : _player) {
		list.second->Update();
	}
	return true;
};

bool PlayerManeger::Add(Player* player){
	_player.push_back(std::make_pair("player",player));
    return true;
};

bool PlayerManeger::Add(std::vector<std::pair<XInput*, int>> param) {
	for (int i = 0; i < param.size(); i++) {
		std::string name = "Player" + std::to_string(i + 1);
		_player.push_back(std::make_pair(name, NEW Player(name,param[i])));
	}
	return true;
};

std::string PlayerManeger::GetListName(std::string name){
	for (auto&& list : _player) {
		std::string str = list.first;
		if (str == name) {
			return str;
		}
	}
	return "";
};

int PlayerManeger::GetListSize(){
	return _player.size();
};

bool PlayerManeger::Draw(){
	for(auto&& list : _player){
		list.second->DebugDraw();
	}
	return true;
}