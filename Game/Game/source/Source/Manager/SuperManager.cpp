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
	DelAll();
	_instance = nullptr;
};

bool SuperManager::Init() {
	return true;
};

bool SuperManager::Add(std::string name,int id, ManagerBase* manager){
	_superManager.emplace_back(std::make_tuple(name,id,manager));
	_isSort = true;
	return true;
};

bool SuperManager::DeleteName(std::string name){
	_delSuperManager.emplace_back(name);
	return true;
};

bool SuperManager::DelAll(){
	for (auto&& list : _superManager) {
		std::get<2>(list)->Terminate();
	}
	for (auto&& list : _superManager) {
		delete std::get<2>(list);
	}
	_superManager.clear();
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

	for (auto&& list : _delSuperManager) {
		for (auto itr = _superManager.begin(); itr != _superManager.end(); ++itr) {
			if (std::get<0>((*itr)) == list) {
				delete std::get<2>((*itr));
				_superManager.erase(itr);
				break;
			}
		}
	}

	_delSuperManager.clear();
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
