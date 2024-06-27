#include "../../Header/UI/UIStartCount.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Other/TimeLimit.h"
#include "../AppFrame/source/Application/Global.h"
#include "../AppFrame/source/System/Header/Resource/ResourceServer.h"
UIStartCount::UIStartCount() : UIRotaBase(){
	_name = "countDown";
	_layer = 20;
	for(int i = 1; i <= 3 ; i++){
		std::string num = std::to_string(i);
		_startCountHandle[i-1] = ResourceServer::LoadGraph("StartCount_" + num,("Res/UI/Count/number_" + num + ".png").c_str());
	}
	int x,y,depth,handleX,handleY;
	GetScreenState(&x,&y,&depth);
	GetGraphSize(_startCountHandle[0], &handleX, &handleY);
	_pos = Vector3D(x/2,y/2,0);
	_center = Vector3D(handleX / 2, handleY / 2, 0);
	_currentTime= GetNowCount();
	SuperManager::GetInstance()->GetManager("uiManager")->Add(this);
	global._soundServer->DirectPlay("SE_CountDown");
};

UIStartCount::~UIStartCount(){
	TimeLimit::GetInstance()->Restart();
};

void UIStartCount::Update(){
	int countDown = 2700 - (GetNowCount() - _currentTime);//2.7•b
	int count = countDown > 0 ? countDown / 900 : 0;//3•ªŠ„
	_handle = _startCountHandle[count];
	SuperManager::GetInstance()->Skip();
	if(countDown < 0){
		SuperManager::GetInstance()->GetManager("uiManager")->DeleteName("countDown");
	}
};
