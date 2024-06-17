#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/Base/UIBase.h"
UIManager::UIManager(){

};

UIManager::~UIManager(){

};

bool UIManager::Init(){
	return true;
};

void UIManager::Add(std::string name, int layer,UIBase* ui){
	_addUiList.emplace_back(std::make_tuple(name,layer,ui));
};

void UIManager::Del(std::string ui){
	_delUiList.emplace_back(ui);
};

void UIManager::DelAll(){
	for (auto&& list : _uiList) {
		delete std::get<2>(list);
	}
	for (auto&& list : _addUiList) {
		delete std::get<2>(list);
	}
	_uiList.clear();
	_addUiList.clear();
	_delUiList.clear();
};

void UIManager::Sort() {
	std::sort(_uiList.begin(), _uiList.end(), [](const std::tuple<std::string, int, UIBase*>& a, const std::tuple<std::string, int, UIBase*>& b) {
		return std::get<1>(a) < std::get<1>(b);
	});
};

int UIManager::GetListSize(){
	return _uiList.size();
}

std::vector<std::tuple<std::string, int,UIBase*>>* UIManager::GetUiList()
{
	return &_uiList;
}

bool UIManager::UpdateInit(){
	// deleteListの中に値があるとき削除
	for (auto list : _delUiList) {
		for (auto itr = _uiList.begin(); itr != _uiList.end();++itr) {
			if (std::get<0>(*itr) == list) {
				delete std::get<2>(*itr);
				_uiList.erase(itr);
				break;
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
		std::get<2>(ui)->Update();
	}

	return true;
};

bool UIManager::Draw(){
	for (auto&& ui : _uiList) {
		std::get<2>(ui)->Draw();
	}
	return true;
};