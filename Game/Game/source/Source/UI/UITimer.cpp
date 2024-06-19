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
	_handle = LoadGraph("Res/UI/Time/flame.png");
	int screenX,screenY,handleX,handleY,depth;
	GetScreenState(&screenX, &screenY, &depth);
	GetGraphSize(_handle, &handleX, &handleY);
	_center = Vector3D(handleX /2, handleY / 2, 0);
	_pos = Vector3D(screenX/2, handleY / 2, 0);

	// ŽžŠÔ‚Ì‰Šú‰»
	GetGraphSize(_timeHandle[0], &handleX, &handleY);
	_timeHandlePos = _pos;
	_timeHandleCenter = Vector3D(handleX, handleY / 2, 0);

	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add("Time", 1, this);
};

UITimer::~UITimer(){

};

void UITimer::Draw(){
	int time = _timer->GetRemainingTime();
	int w = (_timeHandleCenter.x / 2) * _timer->GetDigits();
	float rate = _screenSize.x / 1920;
	// ˜g‚Ì•`‰æ
	UIRotaBase::Draw();
	// ŽžŠÔ‚Ì•`‰æ
	do
	{
		DrawRotaGraph3(_timeHandlePos.x*rate + w * rate, _timeHandlePos.y * rate,
			_timeHandleCenter.x * rate, _timeHandleCenter.y * rate,
			1.0f * rate, 1.0f * rate, 0, _timeHandle[time%10], TRUE);
		time/=10;
		w -= _timeHandleCenter.x;
	}
	while(time > 0);
};
