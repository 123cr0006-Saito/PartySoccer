#pragma once
#include "../../../AppFrame/source/Mode/ModeBase.h"
#include "../../../AppFrame/source/System/Header/Input/XInput.h"
#include "../../../AppFrame/source/System/Header/Function/Vector3D.h"
#include "../Manager/PlayerManeger.h"
#include <utility>
#include <algorithm>

class ModeSelectPlayer : public ModeBase
{
public:
	ModeSelectPlayer();
	~ModeSelectPlayer();

	virtual bool	Initialize();
	virtual bool	Terminate();
	virtual bool	Process();
	virtual bool	Render();

	bool PlayerNumAdjust();
	bool PlayerSelect();

protected:
	std::vector<std::pair<XInput*,int>> _playerParam; // <�R���g���[���[,�I���L�����N�^�[>
	std::vector<std::pair<bool,int>> _selectCharacter; // <�I���I���`�F�b�N,�I���ς݃L�����N�^�[>
	PlayerManeger* _playerManeger;
};

