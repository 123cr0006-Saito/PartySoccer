#include "../../Header/Manager/ObjectManager.h"
ObjectManager::ObjectManager(){

};

ObjectManager::~ObjectManager(){

};

bool ObjectManager::Init() {
	return true;
};

void ObjectManager::Add(std::string name, ObjectBase* object){

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
	for (auto&& list : _objectList) {
		list.second;
	}
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
	_objectList.size();
};