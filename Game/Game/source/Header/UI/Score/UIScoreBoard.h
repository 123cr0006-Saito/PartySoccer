#pragma once
#include "../Base/UIRotaBase.h"
class UIScoreBoard : public UIRotaBase
{
public:
	UIScoreBoard(Vector3D,std::string,class Score*);
	virtual ~UIScoreBoard();
protected:
	class UIScore* _score;
};

