//----------------------------------------------------------------------
// @filename UIPlayerParam.h
// @author: saito ko
// @explanation
// オブジェクトを管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "Base/UIBase.h"
#include <array>
class UIPlayerParam : public UIBase
{
public:
	UIPlayerParam(class Player* player ,const std::string& name, const Vector3D& pos);
	virtual ~UIPlayerParam();
	virtual void Update();
	virtual void Draw();
protected:
	class Player* _player;// プレイヤークラス
	std::array<VERTEX2D, 4> _staminaGauge;// スタミナゲージの頂点
	std::array<VERTEX2D, 4> _shootGauge;// シュートゲージの頂点
};

