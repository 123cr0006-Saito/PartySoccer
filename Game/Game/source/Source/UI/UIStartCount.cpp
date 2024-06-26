#include "../../Header/UI/UIStartCount.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Other/TimeLimit.h"
#include "../AppFrame/source/Application/Global.h"
UIStartCount::UIStartCount() : UIRotaBase(){
	_name = "countDown";
	_layer = 20;
	for(int i = 1; i <= 3 ; i++){
		_startCountHandle[i-1] = LoadGraph(("Res/UI/Count/number_" + std::to_string(i) + ".png").c_str());
	}
	int x,y,depth,handleX,handleY;
	GetScreenState(&x,&y,&depth);
	GetGraphSize(_startCountHandle[0], &handleX, &handleY);
	_pos = Vector3D(x/2,y/2,0);
	_center = Vector3D(handleX / 2, handleY / 2, 0);
	_currentTime= GetNowCount();
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add(this);
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
		dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->DeleteName("countDown");
	}
};
