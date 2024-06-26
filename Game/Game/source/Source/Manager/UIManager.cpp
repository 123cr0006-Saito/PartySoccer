#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/Base/UIBase.h"
UIManager::UIManager(){

};

UIManager::~UIManager(){
	_uiList.clear();
	_addUiList.clear();
	_delUiNameList.clear();
	_delUiList.clear();
};

bool UIManager::Terminate(){
	DelAll();
	return true;
};

bool UIManager::Init(){
	return true;
};

void UIManager::Add(UIBase* ui){
	_addUiList.emplace_back(ui);
};

void UIManager::AddInput(void* value){
	UIBase* ui = static_cast<UIBase*>(value);
	_addUiList.emplace_back(ui);
};

void UIManager::DeleteName(std::string ui){
	_delUiNameList.emplace_back(ui);
};

void UIManager::DeleteInput(void* value){
	UIBase* ui = static_cast<UIBase*>(value);
	_delUiList.emplace_back(ui);
};

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

void UIManager::Sort() {
	std::sort(_uiList.begin(), _uiList.end(), []( UIBase* &a, UIBase* &b) {
		return a->GetLayer() < b->GetLayer();
	});
};

int UIManager::GetListSize(){
	return _uiList.size();
};

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

bool UIManager::Update(){
	// UI�̍X�V
	for (auto&& ui : _uiList) {
		ui->Update();
	}

	return true;
};

bool UIManager::Draw(){
	for (auto&& ui : _uiList) {
		ui->Draw();
	}
	return true;
};