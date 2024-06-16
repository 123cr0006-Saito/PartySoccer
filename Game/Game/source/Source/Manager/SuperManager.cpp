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
};

SuperManager::~SuperManager() {

};

bool SuperManager::Init() {
	return true;
};

bool SuperManager::AddManager(std::string name,int id, ManagerBase* manager){
	_superManager.push_back(std::make_tuple(name,id,manager));
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

bool SuperManager::Update() {
	for (auto&& list : _superManager) {
		std::get<2>(list)->Update();
	}
	return true;
};

bool SuperManager::Draw() {
	for (auto&& list : _superManager) {
		std::get<2>(list)->Draw();
	}
	return true;
};
