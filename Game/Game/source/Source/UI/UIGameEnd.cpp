#include "../../Header/UI/UIGameEnd.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
UIGameEnd::UIGameEnd(){
	_handle = LoadGraph("Res/GameEnd.png");
	int x, y, depth, handleX, handleY;
	GetScreenState(&x, &y, &depth);
	GetGraphSize(_handle, &handleX, &handleY);
	_pos = Vector3D(x / 2, y / 2, 0);
	_center = Vector3D(handleX / 2, handleY / 2, 0);
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add("GameEnd", 100, this);
};

UIGameEnd::~UIGameEnd(){

};

void UIGameEnd::Update(){
	UIRotaBase::Update();
	SuperManager::GetInstance()->Skip();
};