#include "../../Header/Mode/ModeGameEnd.h"
#include "../../Header/UI/UIGameEnd.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../AppFrame/source/System/Header/Function/Easing.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../Header/Mode/ModeResult.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"

ModeGameEnd::ModeGameEnd(){

};

ModeGameEnd::~ModeGameEnd(){
	SuperManager::GetInstance()->GetManager("uiManager")->Del(_ui.first);

};

bool ModeGameEnd::Initialize(){
	_currentTime =GetNowCount();
	UIGameEnd* ui = new UIGameEnd();
	_ui = std::make_pair("GameEnd",ui->GetParam());
	return true;
};

bool ModeGameEnd::Terminate(){
	return true;
};

bool	ModeGameEnd::Process(){
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	int nowTime = GetNowCount() - _currentTime;
	Easing::CallingFunction(&_ui.second->_extrate.x,nowTime,0.0f,1.0f,2000,Easing::Linear);
	Easing::CallingFunction(&_ui.second->_extrate.y, nowTime, 0.0f, 1.0f, 2000, Easing::Linear);
	if(nowTime >2500){
		std::vector<std::string> modeName = {"ModeGame","ModeGameEnd"};
		ModeServer::GetInstance()->Add(NEW ModeResult(), 0, "ModeResult");
		ModeServer::GetInstance()->Add(NEW 	ModeFadeComeBack(2000, modeName, true), 100,"ModeFadeComeBack");
	}
	return true;
};
