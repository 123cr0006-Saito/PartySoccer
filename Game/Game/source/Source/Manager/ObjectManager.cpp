#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Object/Base/ObjectBase.h"
ObjectManager::ObjectManager(){

};

ObjectManager::~ObjectManager(){

};

bool ObjectManager::Init() {
	return true;
};

void ObjectManager::Add(std::string name, ObjectBase* object){
	_objectList.emplace_back(std::make_pair(name, object));
};

void ObjectManager::Del(std::string name){

};

void ObjectManager::DelAll(){
	_objectList.clear();
};

void ObjectManager::Sort() {

};

bool ObjectManager::Update(){
	for (auto&& list : _objectList) {
		list.second->Update();
	}
	return true;
};

bool ObjectManager::UpdateEnd() 
{
	for (auto&& list : _objectList) {
		list.second->UpdateEnd();
	}
	return true;
};

bool ObjectManager::Draw() {
	for (auto&& list : _objectList) {
		list.second->DebugDraw();
	}
	return true;
};

ObjectBase* ObjectManager::Get(std::string name){
	for (auto&& list : _objectList) {
		if (list.first == name) {
			return list.second;
		}
	}
	return nullptr;
};

int ObjectManager::GetListSize() {
	return _objectList.size();
};