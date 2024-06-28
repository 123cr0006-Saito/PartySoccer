//----------------------------------------------------------------------
// @filename UIBase.h
// @author: saito ko
// @explanation
// UIの基底クラス
//----------------------------------------------------------------------
#pragma once
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include <string>
class UIBase
{
public:
	UIBase();
	UIBase(const std::string& name ,const Vector3D& pos,const float alpha,const int handle,const int layer);
	UIBase(const std::string& name ,const Vector3D& pos,const float expansion,const float alpha,const int handle,const int layer);
	virtual ~UIBase();
	virtual void Update();
	virtual void Draw();

	Vector3D GetPos() const { return _pos; }
	std::string GetName() const { return _name; }
	float GetAlpha() const { return _alpha; }
	int GetLayer() const { return _layer; }
	void SetHandle(const int handle) { _handle = handle; }
	void SetPos(const Vector3D& pos) { _pos = pos; }
	void SetAlpha(const float alpha) { _alpha = alpha; }
	void SetPosX(const float x) { _pos.x = x; }
	void SetPosY(const float y) { _pos.y = y; }
protected:
	static Vector3D _screenSize;//画面サイズ
	std::string _name;//名前
	int _handle;//画像ハンドル
	int _layer;//描画順
	Vector3D _pos;//座標
	float _alpha;//透明度
private:
	float _expansionRate;//拡大率
};