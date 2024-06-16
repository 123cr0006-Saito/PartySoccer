#include "../../Header/Manager/PlayerManeger.h"
#include "../MemoryLeak.h"
#include "../AppFrame/source/Application/UtilMacro.h"

PlayerManeger::PlayerManeger() {

};

PlayerManeger::~PlayerManeger(){

};

bool PlayerManeger::Update(){
	for (auto&& list : _player) {
		list.second->Update();
	}
	return true;
};

void PlayerManeger::Add(std::vector<std::pair<XInput*, int>> param) {
	for (int i = 0; i < param.size(); i++) {
		std::string name = "Player" + std::to_string(i + 1);
		_player.push_back(std::make_pair(name, NEW Player(name,param[i])));
	}
};

void PlayerManeger::SetPos(){

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