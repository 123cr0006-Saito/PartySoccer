//----------------------------------------------------------------------
// @filename RenderManager.cpp
// @author: saito ko
// @explanation
// 3D���f���̕`����Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Manager/RenderManager.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../../Header/Model/Base/ModelBase.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
RenderManager::RenderManager() {

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
RenderManager::~RenderManager() {
	_modelList.clear();
	_addModelList.clear();
	_delModelList.clear();
	_delModelNameList.clear();
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool RenderManager::Terminate(){
	return true;
}
//----------------------------------------------------------------------
// @brief �C���X�^���X�̒ǉ�
// @param �ǉ�����C���X�^���X
// @return ����
//----------------------------------------------------------------------
void RenderManager::AddInput(void* value){
	ModelBase* model = static_cast<ModelBase*>(value);
	_addModelList.emplace_back(model);
};
//----------------------------------------------------------------------
// @brief �폜����C���X�^���X�̖��O��}��
// @param �폜�������C���X�^���X�̖��O
// @return ����
//----------------------------------------------------------------------
void RenderManager::DeleteName(std::string name){
	_delModelNameList.emplace_back(name);
};
//----------------------------------------------------------------------
// @brief �C���X�^���X�̍폜
// @param �폜����C���X�^���X
// @return ����
//----------------------------------------------------------------------
void RenderManager::DeleteInput(void* value){
	ModelBase* model = static_cast<ModelBase*>(value);
	_delModelList.emplace_back(model);
};
//----------------------------------------------------------------------
// @brief �i�[���Ă���C���X�^���X�����ׂč폜
// @return ����
//----------------------------------------------------------------------
void RenderManager::DelAll() {
	for(auto&& list : _modelList){
		delete list;
	}
	for(auto&& list : _addModelList){
		delete list;
	}

	_modelList.clear();
	_addModelList.clear();
	_delModelList.clear();
	_delModelNameList.clear();
}
//----------------------------------------------------------------------
// @brief ���f���N���X�̃��C���[�ԍ����Q�Ƃ����Ԃ����ւ���
// @return ����
//----------------------------------------------------------------------
void RenderManager::Sort(){
	std::sort(_modelList.begin(), _modelList.end(), [](ModelBase* a,ModelBase* b) {
		return a->GetLayer() < b->GetLayer();
	});
};
//----------------------------------------------------------------------
// @brief �ǉ����Ă����C���X�^���X�̍폜�ƒǉ�
// @return ����������
//----------------------------------------------------------------------
bool RenderManager::UpdateInit(){
	for (auto list : _delModelList) {
		for (auto itr = _modelList.begin(); itr != _modelList.end();) {
			if ((*itr) == list) {
				delete (*itr);
				itr = _modelList.erase(itr);
			}
			else {
				++itr;
			}
		}
	}

	// deleteList�̒��ɒl������Ƃ��폜
	for (auto list : _delModelNameList) {
		for (auto itr = _modelList.begin(); itr != _modelList.end();) {
			if ((*itr)->GetName() == list) {
				delete (*itr);
				itr = _modelList.erase(itr);
			}
			else{
				++itr;
			}
		}
	}

	bool isSort = false; // �\�[�g���s�����ǂ����̃t���O

	// addList�̒��ɒl������Ƃ��ǉ�
	for (auto list : _addModelList) {
		_modelList.push_back(list);
		isSort = true;
	}

	// ���f����ǉ��������Ƀ\�[�g
	if (isSort) {
		Sort();
	}

	// �O�̂��߃��X�g�̃N���A
	_addModelList.clear();
	_delModelList.clear();
	_delModelNameList.clear();
	return true;
}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool RenderManager::Update() {
	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool RenderManager::Draw() {
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	for (auto list : _modelList) {
		list->Render();
	}
	return true;
};