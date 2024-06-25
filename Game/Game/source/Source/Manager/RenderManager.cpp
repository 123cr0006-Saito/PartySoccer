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

void RenderManager::Add(ModelBase* model){
	_addModelList.emplace_back(model);
};

void RenderManager::AddInput(void* value){
	ModelBase* model = static_cast<ModelBase*>(value);
	_addModelList.emplace_back(model);
};

void RenderManager::Del(std::string name){
	_delModelList.emplace_back(name);
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
	// deleteListの中に値があるとき削除
	for (auto list : _delModelList) {
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