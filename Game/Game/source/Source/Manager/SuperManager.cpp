#include "../../Header/Manager/SuperManager.h"
SuperManager::SuperManager() {

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

bool SuperManager::Update() {
	return true;
};

bool SuperManager::Draw() {
	return true;
};
