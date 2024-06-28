//----------------------------------------------------------------------
// @filename ModeGameEnd.h
// @author: saito ko
// @explanation
// ゲーム終了時の演出を行うクラス
//----------------------------------------------------------------------
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
	int _currentTime;//現在の時間
	class UIGameEnd* _ui;//ゲーム終了時のUI
};

