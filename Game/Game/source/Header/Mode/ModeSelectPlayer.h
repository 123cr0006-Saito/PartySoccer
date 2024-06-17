#pragma once
#include "../../../AppFrame/source/Mode/ModeBase.h"
#include "../../../AppFrame/source/System/Header/Input/XInput.h"
#include "../../../AppFrame/source/System/Header/Function/Vector3D.h"
#include "../Manager/SuperManager.h"
#include "../Manager/PlayerManager.h"
#include <utility>
#include <algorithm>
class ModeSelectPlayer : public ModeBase
{
public:
	ModeSelectPlayer();
	~ModeSelectPlayer();

	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;
	
	bool PlayerNumAdjust();
	bool PlayerSelect();
protected:
	std::vector<std::pair<XInput*,int>> _playerParam; // <コントローラー,選択キャラクター>
	std::vector<std::pair<bool,int>> _selectCharacter; // <選択終了チェック,選択済みキャラクター>
	PlayerManager* _playerManager;
	SuperManager* _superManager;

	std::array<int,4> _modelHandle;
	std::array<VERTEX2D, 4> _vertex;
	int _scrollSpeed;
	int textureHandle;
	int _selectTeamMember;
};

