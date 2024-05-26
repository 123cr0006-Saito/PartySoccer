#include "../../Header/Manager/SuperManager.h"
SuperManager::SuperManager() {

};

SuperManager::~SuperManager() {

};

bool SuperManager::Init() {
	return true;
};

bool SuperManager::AddManager(int id, ManagerBase* manager){
	_superManager.push_back(std::make_pair(id,manager));
	return true;
};

bool SuperManager::Update() {
	return true;
};

bool SuperManager::Draw() {
	return true;
};
