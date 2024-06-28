//----------------------------------------------------------------------
// @filename ModeResult.h
// @author: saito ko
// @explanation
// クリア画面のクラス
//----------------------------------------------------------------------
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
	class SuperManager* _superManager; // スーパーマネージャークラス
	class PlayerManager* _playerManager; // プレイヤーマネージャークラス
	class Score* _score; //点数クラス
	class XInput* _input;//入力クラス
	class Camera* _camera;//カメラクラス
	std::string _winnerTeam; //勝利チームの名前
	int _currentTime;//現在の時間
};

