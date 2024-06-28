#pragma once
#include "../Base/UIRotaBase.h"
#include <unordered_map>
class UIScore : public UIRotaBase
{
public:
	UIScore(const Vector3D& pos,const std::string& name,class Score* score);
	virtual ~UIScore();
	virtual void Update()override;
	virtual void Draw()override;
protected:
	class Score* _score;
	std::string _teamName;
	std::unordered_map<int, int> _scoreHandle;
};