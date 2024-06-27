#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
#include "../../Header/UI/Base/UIRotaBase.h"
#include <array>
class ModeGoal : public ModeBase
{
	public:
	ModeGoal(std::string name);
	~ModeGoal();
	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;

	void LoadUI();
	void AnimationProcess();
protected:
	class SuperManager* _superManager;
	class Score* _score;
	std::vector<std::pair<std::string, UIRotaBase*>> _ui;
	std::array<int,10> _numHandle;
	std::string _name;
	int _nowScore[2];
	int _currentTime;
};

