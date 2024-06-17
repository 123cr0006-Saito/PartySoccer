#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
#include "../../Header/UI/Base/UIRotaBase.h"
class ModeGoal : public ModeBase
{
	public:
	ModeGoal(std::string name);
	~ModeGoal();
	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;

	void LoadUIOnce();
	void AnimationProcess();
protected:
	std::string _name;
	int _nowScore[2];
	class Score* _score;
	static bool _isLoadUI;
	static std::map<std::string, UIRotaParam> _uiParam;
	std::map<std::string, UIRotaParam*> _ui;
	std::unordered_map<int,int> _numHandle;
	int _currentTime;
};

