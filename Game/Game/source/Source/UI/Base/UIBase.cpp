//----------------------------------------------------------------------
// @filename UIBase.cpp
// @author: saito ko
// @explanation
// UIの基底クラス
//----------------------------------------------------------------------
#include "../../../Header/UI/Base/UIBase.h"
#include "../AppFrame/source/Application/Global.h"
//----------------------------------------------------------------------
// 画面サイズを取得
#if !defined(_DEBUG) || defined(FULLSCREEN)
Vector3D UIBase::_screenSize = Vector3D(1920, 1080, 0);
#else
Vector3D UIBase::_screenSize = Vector3D(1280, 720, 0);
#endif
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
UIBase::UIBase() :
	_name(""),
	_expansionRate(1.0f),
	_alpha(255),
	_layer(0),
	_handle(-1)
{
};
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param 名前
// @param 座標
// @param 透明度
// @param 画像ハンドル
// @param レイヤー
// @return 無し
//----------------------------------------------------------------------
UIBase::UIBase(const std::string& name, const Vector3D& pos, const float alpha, const int handle, const int layer) :
	_name(name),
	_pos(pos),
	_alpha(alpha),
	_handle(handle),
	_layer(layer)
{

};
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param 名前
// @param 座標
// @param 拡大率
// @param 透明度
// @param 画像ハンドル
// @param レイヤー
// @return 無し
//----------------------------------------------------------------------
UIBase::UIBase(const std::string& name, const Vector3D& pos, const float expansion, const float alpha, const int handle, const int layer) :
	_name(name),
	_pos(pos),
	_expansionRate(expansion),
	_alpha(alpha),
	_handle(handle),
	_layer(layer)
{

};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
UIBase::~UIBase(){

};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 無し
//----------------------------------------------------------------------
void UIBase::Update(){

};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 無し
//----------------------------------------------------------------------
void UIBase::Draw(){
	float rate = _screenSize.x / 1920;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	DrawRotaGraph(_pos.x * rate,_pos.y * rate, _expansionRate * rate,0.0f,_handle,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};

