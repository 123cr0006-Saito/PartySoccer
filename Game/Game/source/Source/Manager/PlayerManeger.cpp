#include "../../Header/Manager/PlayerManeger.h"
#include "../MemoryLeak.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/source/CFile/CFile.h"
PlayerManeger::PlayerManeger() {
	LoadObjectPos();
};

PlayerManeger::~PlayerManeger(){

};

void PlayerManeger::LoadObjectPos(){
	std::string fileName = "Data/PlayerOriginPos.csv";
	CFile file(fileName);
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			Vector3D pos;
			c += GetFloatNum(&p[c], &pos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.y); //y���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.z); //z���W���擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����
			_originPos.push_back(pos);
		}
	}
	else {
		DebugErrar();
	}
};

bool PlayerManeger::Update(){
	for (auto&& list : _player) {
		list.second->Update();
	}
	return true;
};

bool PlayerManeger::UpdateEnd(){
	for (auto&& list : _player) {
		list.second->UpdateEnd();
	}
	return true;
};

void PlayerManeger::Add(std::vector<std::pair<XInput*, int>> param) {
	for (int i = 0; i < param.size(); i++) {
		std::string name = "Player" + std::to_string(i + 1);
		_player.push_back(std::make_pair(name, NEW Player(name,param[i])));
	}
	SetPos();
};

void PlayerManeger::SetPos(){
	for(int i = 0; i < _player.size(); i++){
		_player[i].second->SetPos(_originPos[i]);
	}
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