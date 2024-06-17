#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
class ModeResult : public ModeBase
{
public:
	ModeResult();
	virtual ~ModeResult();

	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;
protected:
	class SuperManager* _superManager;
	class PlayerManager* _playerManager;
	class Score* _score;
	std::string _winnerTeam;
	class XInput* _input;
};

