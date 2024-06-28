//----------------------------------------------------------------------
// @filename ModeGoal.h
// @author: saito ko
// @explanation
// ゴール時の演出を行うクラス
//----------------------------------------------------------------------
#pragma once
#include "../AppFrame/source/Mode/ModeBase.h"
#include "../../Header/UI/Base/UIRotaBase.h"
#include <array>
class ModeGoal : public ModeBase
{
	public:
	ModeGoal(const std::string& name);
	~ModeGoal();
	virtual bool	Initialize()override;
	virtual bool	Terminate()override;
	virtual bool	Process()override;
	virtual bool	Render()override;

	void LoadUI();
	void AnimationProcess();
protected:
	class SuperManager* _superManager; // スーパーマネージャークラス
	class Score* _score;// 点数クラス
	std::vector<UIRotaBase*> _ui; // UIクラス
	std::array<int,10> _numHandle; // 数字のハンドル
	std::string _name; // 得点を入れたい方の名前
	int _nowScore[2]; // 現在のスコア
	int _currentTime; // 現在の時間
};

