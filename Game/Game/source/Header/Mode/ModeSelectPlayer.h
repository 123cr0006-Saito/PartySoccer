#pragma once
#include "../../../AppFrame/source/Mode/ModeBase.h"
#include "../../../AppFrame/source/System/Header/Input/XInput.h"
#include "../../../AppFrame/source/System/Header/Function/Vector3D.h"
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

	class PlayerManager* _playerManager;
	class SuperManager* _superManager;
	class Camera* _camera;

	std::vector<std::tuple<std::string,XInput*,int>> _playerParam; // <�R���g���[���[,�I���L�����N�^�[>
	std::vector<std::pair<bool,int>> _selectCharacter; // <�I���I���`�F�b�N,�I���ς݃L�����N�^�[>
	std::vector<class UIBase*> _ui;
	std::vector<std::pair<std::string,int>>_modelParam;
	std::unordered_map<std::string,int> _graphHandle;
};

