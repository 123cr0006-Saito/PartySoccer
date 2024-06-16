//----------------------------------------------------------------------
// @filename ModeGame.h
// @date: 2023/12/14
// @author: saito ko
// @explanation
// ボスバトル以外のステージを管理するクラス
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

	bool LoadObject();
	void SetObjePos();
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> LoadObjectParam(std::string fileName);
protected:
	int debug;
	SuperManager* _superManager;
	Player* _player;
	Camera* _camera;
};