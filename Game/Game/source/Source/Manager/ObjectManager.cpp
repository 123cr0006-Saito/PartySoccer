#include "../../Header/Manager/ObjectManager.h"
ObjectManager::ObjectManager(){

};

ObjectManager::~ObjectManager(){

};

bool ObjectManager::Init() {
	return true;
};

void ObjectManager::Add(std::string name, ObjectBase* object){
	_objectList.push_back(std::make_pair(name, object));
};

void ObjectManager::Del(std::string name){

};

void ObjectManager::DelAll(){
	_objectList.clear();
};

void ObjectManager::Sort() {

};

bool ObjectManager::Update(){
	return true;
};

bool ObjectManager::Draw() {
	return true;
};

std::string ObjectManager::GetListName(std::string name){
	for (auto&& list : _objectList) {
		if (list.first == name) {
			return list.first;
		}
	}
	return "";
};

int ObjectManager::GetListSize() {
	return _objectList.size();
};