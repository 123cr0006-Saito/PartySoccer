#include "../../../Header/UI/Score/UIScoreBoard.h"
#include "../../../Header/UI/Score/UIScore.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/UIManager.h"
#include "dxlib.h"
UIScoreBoard::UIScoreBoard(Vector3D pos,std::string name, Score* score) : 
	UIRotaBase()
{
	_param._handle = LoadGraph("Res/GoalAnimation/scoreBoard.png");
	_param._pos = pos;
	int sizeX, sizeY;
	GetGraphSize(_param._handle, &sizeX, &sizeY);
	_param._center = Vector3D(sizeX/2, sizeY/2, 0);
	_score = NEW UIScore(pos, name, score);
	dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"))->Add("scoreBoard", 10, this);
};

UIScoreBoard::~UIScoreBoard(){
	_score = nullptr;
};