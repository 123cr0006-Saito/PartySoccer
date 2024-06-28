//----------------------------------------------------------------------
// @filename ModeGame.h
// @author: saito ko
// @explanation
// ゲーム本編を管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "dxlib.h"
#include "../../../AppFrame/source/Application/UtilMacro.h"

class ModeGame : public ModeBase
{
	typedef ModeBase base;

public:
	ModeGame();
	virtual bool Initialize()override;
	virtual bool Terminate()override;
	virtual bool Process()override;
	virtual bool Render()override;

	bool LoadObject();
	bool LoadUI();
	void ReSetGame();
	std::vector<std::tuple<std::string, Vector3D, Vector3D>> LoadObjectParam(const std::string& fileName);
protected:
	class SuperManager* _superManager;//スーパーマネージャークラス
	class Player* _player;//プレイヤークラス
	class Camera* _camera;//カメラクラス
	class Score* _score;//点数クラス
	class TimeLimit* _timeLimit;//時間制限クラス
	std::vector<std::string> _objectName;//読み込んだオブジェクトの名前を格納する変数

	bool _isAddBall;//ボールを追加するかどうか
	int _currentTime;//現在の時間
};