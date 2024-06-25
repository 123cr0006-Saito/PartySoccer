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

void ObjectManager::Add( ObjectBase* object){
	_objectList.emplace_back(object);
};

void ObjectManager::AddInput(void* value){
	ObjectBase* object = static_cast<ObjectBase*>(value);
	_addObjectList.emplace_back(object);
}

void ObjectManager::Del(std::string name){
	_delObjectList.emplace_back(name);
};

void ObjectManager::DelAll(){
	for (auto&& list : _addObjectList) {
		delete list;
	}
	for(auto&& list : _objectList){
		delete list;
	}
	_objectList.clear();
	_addObjectList.clear();
};

bool ObjectManager::Update(){
	// deleteList‚Ì’†‚É’l‚ª‚ ‚é‚Æ‚«íœ
	for (auto list : _delObjectList) {
		for (auto itr = _objectList.begin(); itr != _objectList.end();) {
			if ((*itr)->GetName() == list) {
				delete (*itr);
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
		list->Update();
	}

	_delObjectList.clear();
	_addObjectList.clear();
	return true;
};

bool ObjectManager::UpdateEnd() 
{
	for (auto&& list : _objectList) {
		list->UpdateEnd();
	}
	return true;
};

bool ObjectManager::Draw() {
#ifdef _DEBUG
	for (auto&& list : _objectList) {
		list->DebugDraw();
	}
#endif
	return true;
};

ObjectBase* ObjectManager::Get(std::string name){
	for (auto&& list : _objectList) {
		if (list->GetName() == name) {
			return list;
		}
	}
	return nullptr;
};

int ObjectManager::GetListSize() {
	return _objectList.size();
};