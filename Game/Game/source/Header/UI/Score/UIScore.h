#pragma once
#include "../Base/UIRotaBase.h"
#include <unordered_map>
class UIScore : public UIRotaBase
{
public:
	UIScore(Vector3D,std::string,class Score*);
	virtual ~UIScore();
	virtual void Update()override;
	virtual void Draw()override;
protected:
	class Score* _score;
	std::string _teamName;
	std::unordered_map<int, int> _scoreHandle;
};