#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Other/TimeLimit.h"
#include "../../Header/UI/UITimer.h"

UITimer::UITimer(TimeLimit* timer){
	_timer = timer;
	for (int i = 0; i < 10; i++) {
		_timeHandle[i] = LoadGraph(("Res/UI/Time/" + std::to_string(i) + ".png").c_str());
	}
	// ˜g‚Ì‰Šú‰»
	param.handle = LoadGraph("Res/UI/Time/flame.png");
	int screenX,screenY,handleX,handleY,depth;
	GetScreenState(&screenX, &screenY, &depth);
	GetGraphSize(param.handle, &handleX, &handleY);	
	param.center = Vector3D(handleX /2, handleY / 2, 0);
	param.pos = Vector3D(screenX/2, handleY / 2, 0);

	// ŽžŠÔ‚Ì‰Šú‰»
	GetGraphSize(_timeHandle[0], &handleX, &handleY);
	_timeHandleParam.pos = param.pos;
	_timeHandleParam.center = Vector3D(handleX, handleY / 2, 0);
	_timeHandleParam.angle = 0;
	_timeHandleParam.extrate = Vector3D(1, 1, 0);
	_timeHandleParam.alpha = 255;

	param.alpha = 255;
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add("Time", 1, this);
};

UITimer::~UITimer(){

};

void UITimer::Draw(){
	int time = _timer->GetRemainingTime();
	int w = (_timeHandleParam.center.x / 2) * _timer->GetDigits();
	float rate = screenSize.x / 1920;
	// ˜g‚Ì•`‰æ
	UIBase::Draw();
	// ŽžŠÔ‚Ì•`‰æ
	do
	{
		DrawRotaGraph3(_timeHandleParam.pos.x*rate + w * rate, _timeHandleParam.pos.y * rate,
			_timeHandleParam.center.x * rate,_timeHandleParam.center.y * rate,
			_timeHandleParam.extrate.x * rate, _timeHandleParam.extrate.y * rate,
			_timeHandleParam.angle, _timeHandle[time%10], TRUE);
		time/=10;
		w -= _timeHandleParam.center.x;
	}
	while(time > 0);
};
