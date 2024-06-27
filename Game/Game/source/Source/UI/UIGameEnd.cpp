//----------------------------------------------------------------------
// @filename UIGameEnd.cpp
// @author: saito ko
// @explanation
// タイムアップ時に終了画面を描画するUIクラス
//----------------------------------------------------------------------
#include "../../Header/UI/UIGameEnd.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../AppFrame/source/Application/Global.h"
#include "../AppFrame/source/System/Header/Resource/ResourceServer.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
UIGameEnd::UIGameEnd(){
	_handle = ResourceServer::LoadGraph("GameEnd","Res/GameEnd.png");
	_name = "GameEnd";
	_layer = 100;
	int x, y, depth, handleX, handleY;
	GetScreenState(&x, &y, &depth);
	GetGraphSize(_handle, &handleX, &handleY);
	_pos = Vector3D(x / 2, y / 2, 0);
	_center = Vector3D(handleX / 2, handleY / 2, 0);
	SuperManager::GetInstance()->GetManager("uiManager")->Add(this);
	global._soundServer->DirectPlay("SE_GameEnd");
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
UIGameEnd::~UIGameEnd(){

};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 無し
//----------------------------------------------------------------------
void UIGameEnd::Update(){
	UIRotaBase::Update();
	SuperManager::GetInstance()->Skip();
};