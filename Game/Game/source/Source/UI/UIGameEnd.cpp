#include "../../Header/UI/UIGameEnd.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../AppFrame/source/Application/Global.h"
UIGameEnd::UIGameEnd(){
	_handle = LoadGraph("Res/GameEnd.png");
	_name = "GameEnd";
	_layer = 100;
	int x, y, depth, handleX, handleY;
	GetScreenState(&x, &y, &depth);
	GetGraphSize(_handle, &handleX, &handleY);
	_pos = Vector3D(x / 2, y / 2, 0);
	_center = Vector3D(handleX / 2, handleY / 2, 0);
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add(this);
	global._soundServer->DirectPlay("SE_GameEnd");
};

UIGameEnd::~UIGameEnd(){

};

void UIGameEnd::Update(){
	UIRotaBase::Update();
	SuperManager::GetInstance()->Skip();
};