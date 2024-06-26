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
ModeGameEnd::ModeGameEnd(){

};

ModeGameEnd::~ModeGameEnd(){
	SuperManager::GetInstance()->GetManager("uiManager")->Del(_ui.first);
};

bool ModeGameEnd::Initialize(){
	_currentTime =GetNowCount();
	UIGameEnd* ui = new UIGameEnd();
	LocationAnim* anim = new LocationAnim(ui, "Data/UIAnimation/GameEndAnimation.csv");
	ui->SetAnimation(anim);
	_ui = std::make_pair("GameEnd",ui);
	return true;
};

bool ModeGameEnd::Terminate(){
	SuperManager::GetInstance()->GetManager("uiManager")->Del(_ui.first);
	return true;
};

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
