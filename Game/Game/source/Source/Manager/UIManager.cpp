//----------------------------------------------------------------------
// @filename UIManager.cpp
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/Base/UIBase.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIManager::UIManager(){

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIManager::~UIManager(){
	_uiList.clear();
	_addUiList.clear();
	_delUiNameList.clear();
	_delUiList.clear();
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool UIManager::Terminate(){
	DelAll();
	return true;
};
//----------------------------------------------------------------------
// @brief �C���X�^���X�̒ǉ�
// @param �ǉ�����C���X�^���X
// @return ����
//----------------------------------------------------------------------
void UIManager::AddInput(void* value){
	UIBase* ui = static_cast<UIBase*>(value);
	_addUiList.emplace_back(ui);
};
//----------------------------------------------------------------------
// @brief �폜����C���X�^���X�̖��O��}��
// @param �폜�������C���X�^���X�̖��O
// @return ����
//----------------------------------------------------------------------
void UIManager::DeleteName(std::string ui){
	_delUiNameList.emplace_back(ui);
};
//----------------------------------------------------------------------
// @brief �C���X�^���X�̍폜
// @param �폜����C���X�^���X
// @return ����
//----------------------------------------------------------------------
void UIManager::DeleteInput(void* value){
	UIBase* ui = static_cast<UIBase*>(value);
	_delUiList.emplace_back(ui);
};
//----------------------------------------------------------------------
// @brief �i�[���Ă���C���X�^���X�����ׂč폜
// @return ����
//----------------------------------------------------------------------
void UIManager::DelAll(){
	for (auto&& list : _uiList) {
		delete list;
	}
	for (auto&& list : _addUiList) {
		delete list;
	}
	_uiList.clear();
	_addUiList.clear();
	_delUiNameList.clear();
};
//----------------------------------------------------------------------
// @brief ���C���[�ԍ����Q�Ƃ����Ԃ����ւ���
// @return ����
//----------------------------------------------------------------------
void UIManager::Sort() {
	std::sort(_uiList.begin(), _uiList.end(), []( UIBase* &a, UIBase* &b) {
		return a->GetLayer() < b->GetLayer();
	});
};
//----------------------------------------------------------------------
// @brief �ǉ����Ă����C���X�^���X�̍폜�ƒǉ�
// @return ����������
//----------------------------------------------------------------------
bool UIManager::UpdateInit(){
	// deleteList�̒��ɒl������Ƃ��폜

	for (auto list : _delUiList) {
		for (auto itr = _uiList.begin(); itr != _uiList.end();) {
			if ((*itr) == list) {
				delete (*itr);
				itr = _uiList.erase(itr);
			}
			else {
				++itr;
			}
		}
	}

	for (auto list : _delUiNameList) {
		for (auto itr = _uiList.begin(); itr != _uiList.end();) {
			if ((*itr)->GetName() == list) {
				delete (*itr);
				itr = _uiList.erase(itr);
			}
			else{
				++itr;
			}
		}
	}

	bool isSort = false; // �\�[�g���s�����ǂ����̃t���O

	// addList�̒��ɒl������Ƃ��ǉ�
	for (auto list : _addUiList) {
		_uiList.emplace_back(list);
		isSort = true;
	}

	// ���f����ǉ��������Ƀ\�[�g
	if (isSort) {
		Sort();
	}

	// addList��deleteList���N���A
	_addUiList.clear();
	_delUiList.clear();
	_delUiNameList.clear();
	return true;
}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool UIManager::Update(){
	// UI�̍X�V
	for (auto&& ui : _uiList) {
		ui->Update();
	}

	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool UIManager::Draw(){
	for (auto&& ui : _uiList) {
		ui->Draw();
	}
	return true;
};