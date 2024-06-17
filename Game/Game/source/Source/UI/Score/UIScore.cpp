#include "../../../Header/UI/Score/UIScore.h"
#include "../../../Header/Other/Score.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/UIManager.h"
#include "../../../Header/Other/Score.h"

UIScore::UIScore(Vector3D pos, std::string name, Score* score) : 
	UIRotaBase(),
	_teamName(name),
	_score(score)
{
	_param._pos = pos;
	for(int i = 0; i < 10; i++){
		_scoreHandle[i] = LoadGraph(("Res/UI/Number/timer_0" + std::to_string(i) + ".png").c_str());
	}
	int sizeX, sizeY;
	GetGraphSize(_scoreHandle[0], &sizeX, &sizeY);
	_param._center = Vector3D(sizeX / 2, sizeY / 2, 0);
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add("scoreNum", 15, this);
};

UIScore::~UIScore(){

};

void UIScore::Update(){

};

void UIScore::Draw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _param._alpha);
	float rate = _screenSize.x / 1920;
	int num = _score->GetScore(_teamName);
	int w = 0;
	if(num >= 10) w = _param._center.x * rate;
	do
	{
		DrawRotaGraph3(_param._pos.x * rate + w, _param._pos.y * rate, _param._center.x * rate, _param._center.y * rate, _param._extrate.x * rate, _param._extrate.y * rate, _param._angle, _scoreHandle[num%10], true);
		w -= _param._center.x * 2 * rate;
		num /= 10;
	}
	while(num > 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};
