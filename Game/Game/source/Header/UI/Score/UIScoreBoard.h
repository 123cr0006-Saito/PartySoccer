#pragma once
#include "../Base/UIBase.h"
class UIScoreBoard : public UIBase
{
public:
	UIScoreBoard(Vector3D,std::string,class Score*);
	virtual ~UIScoreBoard();
protected:
	class UIScore* _score;
};

