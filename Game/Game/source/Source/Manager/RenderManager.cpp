#include "../../Header/Manager/RenderManager.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../../Header/Model/Base/ModelBase.h"

RenderManager::RenderManager() {

};

RenderManager::~RenderManager() {

};

bool RenderManager::Init() {
	return true;
};

void RenderManager::Add( int layer, ModelBase* model){
	_addModelList.emplace_back(std::pair(layer, model));
};

void RenderManager::Del(std::string name){
	_delModelList.emplace_back(name);
};

void RenderManager::DelAll() {
	for(auto&& list : _modelList){
		delete list.second;
	}
	for(auto&& list : _addModelList){
		delete list.second;
	}

	_modelList.clear();
	_addModelList.clear();
	_delModelList.clear();
}

void RenderManager::Sort(){
	std::sort(_modelList.begin(), _modelList.end(), [](const std::pair<int, ModelBase*> a,const std::pair< int, ModelBase*> b) {
		return a.first < b.first;
	});
};

int RenderManager::GetListSize(){
	return _modelList.size();
};

bool RenderManager::UpdateInit(){
	// deleteList�̒��ɒl������Ƃ��폜
	for (auto list : _delModelList) {
		for (auto itr = _modelList.begin(); itr != _modelList.end();++itr) {
			if ((*itr).second->GetName() == list) {
				delete (*itr).second;
				itr = _modelList.erase(itr);
				break;
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
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	for (auto list : _modelList) {
		list.second->Render();
	}
	return true;
};