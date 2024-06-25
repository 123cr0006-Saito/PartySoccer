#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/Base/UIBase.h"
UIManager::UIManager(){

};

UIManager::~UIManager(){

};

bool UIManager::Init(){
	return true;
};

void UIManager::Add(UIBase* ui){
	_addUiList.emplace_back(ui);
};

void UIManager::Del(std::string ui){
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
	_delUiList.clear();
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
	// deleteListの中に値があるとき削除
	for (auto list : _delUiList) {
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

	bool isSort = false; // ソートを行うかどうかのフラグ

	// addListの中に値があるとき追加
	for (auto list : _addUiList) {
		_uiList.emplace_back(list);
		isSort = true;
	}

	// モデルを追加した時にソート
	if (isSort) {
		Sort();
	}

	// addListとdeleteListをクリア
	_addUiList.clear();
	_delUiList.clear();
	return true;
}

bool UIManager::Update(){
	// UIの更新
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