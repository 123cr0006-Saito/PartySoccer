//----------------------------------------------------------------------
// @filename ModeTitle.h
// @author: saito ko
// @explanation
// タイトル画面を描画するクラス
//----------------------------------------------------------------------
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
	class XInput* _input; //入力クラス
	class SuperManager* _superManager;//スーパーマネージャー
	std::vector<std::string> _uiName;//UIの名前
};

