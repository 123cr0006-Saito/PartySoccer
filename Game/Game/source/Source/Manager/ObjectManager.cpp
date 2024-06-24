#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Object/Base/ObjectBase.h"
ObjectManager::ObjectManager(){

};

ObjectManager::~ObjectManager(){
	DelAll();
};

bool ObjectManager::Init() {
	return true;
};

void ObjectManager::Add(std::string name, ObjectBase* object){
	_objectList.emplace_back(std::make_pair(name, object));
};

void ObjectManager::Del(std::string name){
	_delObjectList.emplace_back(name);
};

void ObjectManager::DelAll(){
	for (auto&& list : _addObjectList) {
		delete list.second;
	}
	for(auto&& list : _objectList){
		delete list.second;
	}
	_objectList.clear();
	_addObjectList.clear();
};

void ObjectManager::Sort() {

};

bool ObjectManager::Update(){
	// deleteList‚Ì’†‚É’l‚ª‚ ‚é‚Æ‚«íœ
	for (auto list : _delObjectList) {
		for (auto itr = _objectList.begin(); itr != _objectList.end();) {
			if (itr->first == list) {
				delete itr->second;
			  itr = _objectList.erase(itr);
			}
			else{
				++itr;
			}
		}
	}

	// addList‚Ì’†‚É’l‚ª‚ ‚é‚Æ‚«’Ç‰Á
	for (auto list : _addObjectList) {
		_objectList.emplace_back(list);
	}

	for (auto&& list : _objectList) {
		list.second->Update();
	}

	_delObjectList.clear();
	_addObjectList.clear();
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
#ifdef _DEBUG
	for (auto&& list : _objectList) {
		list.second->DebugDraw();
	}
#endif
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