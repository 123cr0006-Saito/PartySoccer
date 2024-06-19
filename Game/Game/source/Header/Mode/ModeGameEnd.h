#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
class ModeGameEnd : public ModeBase
{
public:
	ModeGameEnd();
	~ModeGameEnd();
	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
protected:
	int _currentTime;
	std::pair<std::string , class UIGameEnd*> _ui;
};

