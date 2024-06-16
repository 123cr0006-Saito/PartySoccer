#include "../../../Header/UI/Score/UIScoreBoard.h"
#include "../../../Header/UI/Score/UIScore.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/UIManager.h"
#include "dxlib.h"
UIScoreBoard::UIScoreBoard(Vector3D pos,std::string name, Score* score) : 
	UIBase()
{
	param.alpha = 255;
	param.handle = LoadGraph("Res/GoalAnimation/scoreBoard.png");
	param.pos = pos;
	int sizeX, sizeY;
	GetGraphSize(param.handle, &sizeX, &sizeY);
	param.center = Vector3D(sizeX/2, sizeY/2, 0);
	_score = NEW UIScore(pos, name, score);
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add("scoreBoard", 10, this);
};

UIScoreBoard::~UIScoreBoard(){

};