#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Object/Base/ObjectBase.h"
ObjectManager::ObjectManager(){

};

ObjectManager::~ObjectManager(){
	
};

bool ObjectManager::Terminate(){
	DelAll();
	return true;
}

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

void ObjectManager::DeleteName(std::string name){
	_delObjectNameList.emplace_back(name);
};

void ObjectManager::DeleteInput(void* value){
	ObjectBase* object = static_cast<ObjectBase*>(value);
	_delObjectList.emplace_back(object);
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

	for(auto list : _delObjectList) {
		for (auto itr = _objectList.begin(); itr != _objectList.end();) {
			if ((*itr) == list) {
				delete (*itr);
				itr = _objectList.erase(itr);
			}
			else{
				++itr;
			}
		}
	}

	// deleteList�̒��ɒl������Ƃ��폜
	for (auto list : _delObjectNameList) {
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

	// addList�̒��ɒl������Ƃ��ǉ�
	for (auto list : _addObjectList) {
		_objectList.emplace_back(list);
	}

	for (auto&& list : _objectList) {
		list->Update();
	}

	_delObjectList.clear();
	_delObjectNameList.clear();
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