#include "../../Header/Manager/PlayerManager.h"
#include "../MemoryLeak.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/source/CFile/CFile.h"
PlayerManager::PlayerManager() {
	LoadObjectPos();
};

PlayerManager::~PlayerManager(){
	DelAll();
};

void PlayerManager::LoadObjectPos(){
	std::string fileName = "Data/PlayerOriginPos.csv";
	CFile file(fileName);
	// ファイルが開けた場合
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			Vector3D pos;
			c += GetFloatNum(&p[c], &pos.x); //x座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.y); //y座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.z); //z座標を取得
			c += SkipSpace(&p[c], &p[size]); // 空白やコントロールコードをスキップする
			_originPos.push_back(pos);
		}
	}
	else {
		DebugErrar();
	}
};

bool PlayerManager::Update(){
	for (auto&& list : _player) {
		list.second->Update();
	}
	return true;
};

bool PlayerManager::UpdateEnd(){
	for (auto&& list : _player) {
		list.second->UpdateEnd();
	}
	return true;
};

void PlayerManager::Add(std::vector<std::tuple<std::string, XInput*, int>> param) {
	for (int i = 0; i < param.size(); i++) {
		std::string name = "Player" + std::to_string(i + 1);
		_player.emplace_back(std::make_pair(name, NEW Player(std::get<0>(param[i]), std::get<1>(param[i]), std::get<2>(param[i]))));
	}
	SetPos();
};

void PlayerManager::DelAll(){
	for (auto&& list : _player) {
		delete list.second;
	}
	_player.clear();
	_originPos.clear();
};

void PlayerManager::SetPos(){
	for(int i = 0; i < _player.size(); i++){
		_player[i].second->SetPos(Vector3D(1500.0f * pow(-1, i), 0,i / 2 * 2000.0f));
	}
};

int PlayerManager::GetListSize(){
	return _player.size();
};

bool PlayerManager::Draw(){
	for(auto&& list : _player){
		list.second->DebugDraw();
	}
	return true;
}