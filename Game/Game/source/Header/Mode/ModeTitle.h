#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
#include "../../Header/UI/Base/UIRotaBase.h"
class ModeTitle : public ModeBase
{
public:
	ModeTitle();
	virtual ~ModeTitle();

	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;
protected:
	class XInput* _input;
	class SuperManager* _superManager;
	std::map<std::string, UIRotaParam> _uiParam;
	std::map<std::string, UIRotaParam*> _ui;
	std::array<int, 4> _handleShiftValue;
};

