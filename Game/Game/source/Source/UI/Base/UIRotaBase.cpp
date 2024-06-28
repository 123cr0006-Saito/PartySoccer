//----------------------------------------------------------------------
// @filename UIRotaBase.cpp
// @author: saito ko
// @explanation
// オブジェクトを管理するクラス
//----------------------------------------------------------------------
#include "../../../Header/UI/Base/UIRotaBase.h"
#include "../../../Header/UI/Animation/AnimationBase.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
UIRotaBase::UIRotaBase() :
	UIBase(),
	_extrate(Vector3D(1, 1, 1)),
	_angle(0)
{
};
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param オブジェクトの名前
// @param 位置
// @param 中心
// @param 拡大率
// @param 角度
// @param 透明度
// @param 画像ハンドル
// @param レイヤー
// @return 無し
//----------------------------------------------------------------------
UIRotaBase::UIRotaBase(const std::string& name, const Vector3D& pos, const Vector3D& center, const Vector3D& extrate, const float angle, const int alpha, const int handle, const int layer):
UIBase(name,pos,alpha,handle,layer),
_center(center),
_extrate(extrate),
_angle(angle)
{
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
UIRotaBase::~UIRotaBase() {
	if (!_animation.empty()) {
		for (auto&& list : _animation) {
			delete list;
		}
	}
	_animation.clear();
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 無し
//----------------------------------------------------------------------
void UIRotaBase::Update() {
	if(!_animation.empty()){
		for(auto&& list : _animation){
			list->Update();
		}
	}
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 無し
//----------------------------------------------------------------------
void UIRotaBase::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	float rate = _screenSize.x / 1920;
	DrawRotaGraph3(_pos.x * rate, _pos.y * rate, _center.x * rate, _center.y * rate, _extrate.x * rate, _extrate.y * rate, _angle, _handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}