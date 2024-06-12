//----------------------------------------------------------------------
// @filename ModeGame.h
// @date: 2023/12/14
// @author: saito ko
// @explanation
// �{�X�o�g���ȊO�̃X�e�[�W���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "dxlib.h"
#include "../Manager/SuperManager.h"
#include "../Manager/RenderManager.h"
#include "../../../AppFrame/source/Application/UtilMacro.h"
#include "../../Header/Object/Player/Player.h"
#include "../../Header/Other/Camera/Camera.h"
class ModeGame : public ModeBase
{
	typedef ModeBase base;

public:

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	std::vector<std::tuple<Vector3D, Vector3D, Vector3D>> WallLoad();
protected:
	int debug;
	SuperManager* _superManager;
	Player* _player;
	Camera* _camera;
};