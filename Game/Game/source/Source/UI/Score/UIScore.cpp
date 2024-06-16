#include "../../../Header/UI/Score/UIScore.h"
#include "../../../Header/Other/Score.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/UIManager.h"
#include "../../../Header/Other/Score.h"

UIScore::UIScore(Vector3D pos, std::string name, Score* score) : 
	UIBase(),
	_teamName(name),
	_score(score)
{
	param.alpha = 255;
	param.pos = pos;
	for(int i = 0; i < 10; i++){
		_scoreHandle[i] = LoadGraph(("Res/UI/Number/timer_0" + std::to_string(i) + ".png").c_str());
	}
	int sizeX, sizeY;
	GetGraphSize(_scoreHandle[0], &sizeX, &sizeY);
	param.center = Vector3D(sizeX / 2, sizeY / 2, 0);
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add("scoreNum", 15, this);
};

UIScore::~UIScore(){
	for (auto& handle : _scoreHandle) {
		DeleteGraph(handle.second);
	}
};

void UIScore::Update(){

};

void UIScore::Draw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, param.alpha);
	float rate = screenSize.x / 1920;
	int num = _score->GetScore(_teamName);
	int w = 0;
	if(num >= 10) w = param.center.x * rate;
	do
	{
		DrawRotaGraph3(param.pos.x * rate + w, param.pos.y * rate, param.center.x * rate, param.center.y * rate, param.extrate.x * rate, param.extrate.y * rate, param.angle, _scoreHandle[num%10], true);
		w -= param.center.x * 2 * rate;
		num /= 10;
	}
	while(num > 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};
