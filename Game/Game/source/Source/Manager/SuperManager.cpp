#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/ManagerBase.h"
#include "../AppFrame/source/Application/UtilMacro.h"
SuperManager* SuperManager::_instance = nullptr;
SuperManager::SuperManager() {
	if (_instance != nullptr) {
		DebugErrar();
		return;
	}
	_instance = this;
	_isSort = false;
	_isProcessSkip = false;
};

SuperManager::~SuperManager() {

};

bool SuperManager::Init() {
	return true;
};

bool SuperManager::AddManager(std::string name,int id, ManagerBase* manager){
	_superManager.push_back(std::make_tuple(name,id,manager));
	_isSort = true;
	return true;
};

ManagerBase* SuperManager::GetManager(std::string name){
	for (auto&& list : _superManager) {
		if (std::get<0>(list) == name) {
			return std::get<2>(list);
		}
	}
	return nullptr;
};

void SuperManager::Sort(){
	std::sort(_superManager.begin(), _superManager.end(), [](const std::tuple<std::string, int, ManagerBase*>& a, const std::tuple<std::string, int, ManagerBase*>& b) {
		return std::get<1>(a) < std::get<1>(b);
	});
};

bool SuperManager::Update() {

	_isProcessSkip = false;
	if (_isSort) {
		Sort();
		_isSort = false;
	}

	for(auto itr = _superManager.rbegin() ; itr != _superManager.rend(); ++itr){
		std::get<2>((*itr))->UpdateInit();
		if(!_isProcessSkip){
			//スキップが選択されていたら処理をスキップ
			std::get<2>((*itr))->Update();
		}
		std::get<2>((*itr))->UpdateEnd();
	}
	
	return true;
};

bool SuperManager::Draw() {
	for (auto&& list : _superManager) {
		std::get<2>(list)->Draw();
	}
	return true;
};
