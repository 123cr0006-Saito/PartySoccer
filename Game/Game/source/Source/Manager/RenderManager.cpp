#include "../../Header/Manager/RenderManager.h"
#include "../AppFrame/source/Application/UtilMacro.h"

RenderManager::RenderManager() {

};

RenderManager::~RenderManager() {

};

bool RenderManager::Init() {
	return true;
};

void RenderManager::Add(std::string name, int layer, int model){
	_addModelList.push_back(std::make_tuple(name, layer, model));
};

void RenderManager::Del(std::string name){
	_delModelList.push_back(name);
};

void RenderManager::DelAll() {
	_modelList.clear();
	_addModelList.clear();
	_delModelList.clear();
}

void RenderManager::Sort(){
	std::sort(_modelList.begin(), _modelList.end(), [](const std::tuple<std::string, int, int> a,const std::tuple<std::string, int, int> b) {
		return std::get<1>(a) < std::get<1>(b);
	});
};

int RenderManager::GetListSize(){
	return _modelList.size();
};

bool RenderManager::UpdateInit(){
	// deleteList�̒��ɒl������Ƃ��폜
	for (auto list : _delModelList) {
		for (auto itr = _modelList.begin(); itr != _modelList.end();) {
			if (std::get<0>(*itr) == list) {
				itr = _modelList.erase(itr);
			}
			else {
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
	return true;
}

bool RenderManager::Update() {
	return true;
};

bool RenderManager::Draw() {
	for (auto list : _modelList) {
		MV1DrawModel(std::get<2>(list));
	}
	return true;
};