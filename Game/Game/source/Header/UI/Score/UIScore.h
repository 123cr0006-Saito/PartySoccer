//----------------------------------------------------------------------
// @filename UIScore.h
// @author: saito ko
// @explanation
// スコアを描画するUIクラス
//----------------------------------------------------------------------
#pragma once
#include "../Base/UIRotaBase.h"
#include <array>
class UIScore : public UIRotaBase
{
public:
	UIScore(const Vector3D& pos,const std::string& name,class Score* score);
	virtual ~UIScore();
	virtual void Update()override;
	virtual void Draw()override;
protected:
	class Score* _score;//スコアクラス
	std::string _teamName;//チーム名
	std::array<int, 10> _scoreHandle;//スコアのハンドル
};