//----------------------------------------------------------------------
// @filename ModeGameEnd.cpp
// @author: saito ko
// @explanation
// ゲーム終了時の演出を行うクラス
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeGameEnd.h"
#include "../../Header/UI/UIGameEnd.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../AppFrame/source/System/Header/Function/Easing.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../Header/Mode/ModeResult.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/Animation/LocationAnim.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
ModeGameEnd::ModeGameEnd(){

};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
ModeGameEnd::~ModeGameEnd(){

};
//----------------------------------------------------------------------
// @brief 初期化処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeGameEnd::Initialize(){
	_currentTime = GetNowCount();
	// 終了UIを作成
	_ui = NEW UIGameEnd();
	LocationAnim* anim = new LocationAnim(_ui, "Data/UIAnimation/GameEndAnimation.csv");
	_ui->SetAnimation(anim);
	return true;
};
//----------------------------------------------------------------------
// @brief 終了処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeGameEnd::Terminate(){
	// UIを削除
	SuperManager::GetInstance()->GetManager("uiManager")->DeleteName(_ui->GetName());
	return true;
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeGameEnd::Process(){
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	int nowTime = GetNowCount() - _currentTime;
	if(nowTime >2500 && !ModeServer::GetInstance()->Search("ModeFadeComeBack")) {
		std::vector<std::string> modeName = {"ModeGame","ModeGameEnd"};
		ModeServer::GetInstance()->Add(NEW ModeResult(), 0, "ModeResult");
		ModeServer::GetInstance()->Add(NEW 	ModeFadeComeBack(500, modeName, false), 100,"ModeFadeComeBack");
	}
	return true;
};
