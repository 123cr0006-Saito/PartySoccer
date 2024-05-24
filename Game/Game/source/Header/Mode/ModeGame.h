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
class ModeGame : public ModeBase
{
	typedef ModeBase base;


public:

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	
protected:
	int debug;
};