//----------------------------------------------------------------------
// @filename ObjectManager.cpp
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Manager/ObjectManager.h"
#include "../../Header/Object/Base/ObjectBase.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
ObjectManager::ObjectManager(){

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
ObjectManager::~ObjectManager(){
	
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ObjectManager::Terminate(){
	DelAll();
	return true;
}
//----------------------------------------------------------------------
// @brief �C���X�^���X�̒ǉ�
// @param �ǉ�����C���X�^���X
// @return ����
//----------------------------------------------------------------------
void ObjectManager::AddInput(void* value){
	ObjectBase* object = static_cast<ObjectBase*>(value);
	_addObjectList.emplace_back(object);
}
//----------------------------------------------------------------------
// @brief �폜����C���X�^���X�̖��O��}��
// @param �폜�������C���X�^���X�̖��O
// @return ����
//----------------------------------------------------------------------
void ObjectManager::DeleteName(const std::string& name){
	_delObjectNameList.emplace_back(name);
};
//----------------------------------------------------------------------
// @brief �C���X�^���X�̍폜
// @param �폜����C���X�^���X
// @return ����
//----------------------------------------------------------------------
void ObjectManager::DeleteInput(void* value){
	ObjectBase* object = static_cast<ObjectBase*>(value);
	_delObjectList.emplace_back(object);
};
//----------------------------------------------------------------------
// @brief �i�[���Ă���C���X�^���X�����ׂč폜
// @return ����
//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
// @brief �ǉ����Ă����C���X�^���X�̍폜�ƒǉ�
// @return ����������
//----------------------------------------------------------------------
bool ObjectManager::UpdateInit(){
	for (auto list : _delObjectList) {
		for (auto itr = _objectList.begin(); itr != _objectList.end();) {
			if ((*itr) == list) {
				delete (*itr);
				itr = _objectList.erase(itr);
			}
			else {
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
			else {
				++itr;
			}
		}
	}

	// addList�̒��ɒl������Ƃ��ǉ�
	for (auto list : _addObjectList) {
		_objectList.emplace_back(list);
	}

	_delObjectList.clear();
	_delObjectNameList.clear();
	_addObjectList.clear();
	return true;
}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ObjectManager::Update(){
	for (auto&& list : _objectList) {
		list->Update();
	}

	return true;
};
//----------------------------------------------------------------------
// @brief �X�V�I����ɍs������
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ObjectManager::UpdateEnd() 
{
	for (auto&& list : _objectList) {
		list->UpdateEnd();
	}
	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ObjectManager::Draw() {
#ifdef _DEBUG
	for (auto&& list : _objectList) {
		list->DebugDraw();
	}
#endif
	return true;
};
//----------------------------------------------------------------------
// @brief �I�u�W�F�N�g�𖼑O�Ō������擾����
// @param �擾�������C���X�^���X�̖��O
// @return �擾�ł����ꍇ�C���X�^���X��Ԃ��@�ł��Ȃ������ꍇ��nullptr
//----------------------------------------------------------------------
ObjectBase* ObjectManager::Get(const std::string& name){
	for (auto&& list : _objectList) {
		if (list->GetName() == name) {
			return list;
		}
	}
	return nullptr;
};