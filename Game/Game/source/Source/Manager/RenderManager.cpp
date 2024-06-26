#include "../../Header/Manager/RenderManager.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../../Header/Model/Base/ModelBase.h"

RenderManager::RenderManager() {

};

RenderManager::~RenderManager() {
	_modelList.clear();
	_addModelList.clear();
	_delModelList.clear();
	_delModelNameList.clear();
};

bool RenderManager::Terminate(){
	return true;
}

bool RenderManager::Init() {
	return true;
};

void RenderManager::Add(ModelBase* model){
	_addModelList.emplace_back(model);
};

void RenderManager::AddInput(void* value){
	ModelBase* model = static_cast<ModelBase*>(value);
	_addModelList.emplace_back(model);
};

void RenderManager::DeleteName(std::string name){
	_delModelNameList.emplace_back(name);
};

void RenderManager::DeleteInput(void* value){
	ModelBase* model = static_cast<ModelBase*>(value);
	_delModelList.emplace_back(model);
};

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

void RenderManager::Sort(){
	std::sort(_modelList.begin(), _modelList.end(), [](ModelBase* a,ModelBase* b) {
		return a->GetLayer() < b->GetLayer();
	});
};

int RenderManager::GetListSize(){
	return _modelList.size();
};

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

	// deleteListの中に値があるとき削除
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

	bool isSort = false; // ソートを行うかどうかのフラグ

	// addListの中に値があるとき追加
	for (auto list : _addModelList) {
		_modelList.push_back(list);
		isSort = true;
	}

	// モデルを追加した時にソート
	if (isSort) {
		Sort();
	}

	// 念のためリストのクリア
	_addModelList.clear();
	_delModelList.clear();
	_delModelNameList.clear();
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
		list->Render();
	}
	return true;
};