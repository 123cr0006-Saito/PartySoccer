//----------------------------------------------------------------------
// @filename UITimer.cpp
// @author: saito ko
// @explanation
// 残り時間を描画するクラス
//----------------------------------------------------------------------
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Other/TimeLimit.h"
#include "../../Header/UI/UITimer.h"
#include "../AppFrame/source/System/Header/Resource/ResourceServer.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param 時間制限クラス
// @return 無し
//----------------------------------------------------------------------
UITimer::UITimer(TimeLimit* timer){
	_timer = timer;
	_name = "Time";
	_layer = 1;
	for (int i = 0; i < 10; i++) {
		std::string num = std::to_string(i);
		_timeHandle[i] = ResourceServer::LoadGraph("Time_" + num,("Res/UI/Time/" + num + ".png").c_str());
	}
	// 枠の初期化
	_handle = ResourceServer::LoadGraph("TimeFlame","Res/UI/Time/flame.png");
	int screenX,screenY,handleX,handleY,depth;
	GetScreenState(&screenX, &screenY, &depth);
	GetGraphSize(_handle, &handleX, &handleY);
	_center = Vector3D(handleX /2, handleY / 2, 0);
	_pos = Vector3D(screenX/2, handleY / 2, 0);

	// 時間の初期化
	GetGraphSize(_timeHandle[0], &handleX, &handleY);
	_timeHandlePos = _pos;
	_timeHandleCenter = Vector3D(handleX, handleY / 2, 0);

	SuperManager::GetInstance()->GetManager("uiManager")->Add(this);
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
UITimer::~UITimer(){

};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
void UITimer::Draw(){
	int time = _timer->GetRemainingTime();
	int w = (_timeHandleCenter.x / 2) * _timer->GetDigits();
	float rate = _screenSize.x / 1920;
	// 枠の描画
	UIRotaBase::Draw();
	// 時間の描画
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
