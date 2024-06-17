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
	// deleteList�̒��ɒl������Ƃ��폜
	for (auto list : _delUiList) {
		for (auto itr = _uiList.begin(); itr != _uiList.end();++itr) {
			if (std::get<0>(*itr) == list) {
				delete std::get<2>(*itr);
				_uiList.erase(itr);
				break;
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
	return true;
}

bool UIManager::Update(){
	// UI�̍X�V
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