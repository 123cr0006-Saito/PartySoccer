#pragma once
#include "../Base/UIRotaBase.h"
class UIScoreBoard : public UIRotaBase
{
public:
	UIScoreBoard(const Vector3D& pos,const std::string& name ,class Score*);
	virtual ~UIScoreBoard();
protected:
	class UIScore* _score;
};

