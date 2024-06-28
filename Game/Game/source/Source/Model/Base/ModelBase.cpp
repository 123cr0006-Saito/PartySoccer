//----------------------------------------------------------------------
// @filename ModelBase.cpp
// @author: saito ko
// @explanation
// 3Dモデルを管理する基底クラス
//----------------------------------------------------------------------
#include "../../../Header/Model/Base/ModelBase.h"
#include "../AppFrame/source/System/Header/Function/Vector3D.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
ModelBase::ModelBase() :
	_name(""),
	_layer(0),
	_modelHandle(0),
	_vertexShader(0),
	_pixelShader(0),
	_isShader(false)
{
};
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param モデルの名前
// @param レイヤー番号
// @param モデルハンドル
// @return 無し
//----------------------------------------------------------------------
ModelBase::ModelBase(const std::string& name, const int layer, const int handle) :
	_name(name),
	_layer(layer),
	_modelHandle(handle),
	_vertexShader(0),
	_pixelShader(0),
	_isShader(false)
{
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
ModelBase::~ModelBase(){

};
//----------------------------------------------------------------------
// @brief モデルの座標を設定
// @param 座標
// @return 無し
//----------------------------------------------------------------------
void ModelBase::SetPos(const Vector3D& pos){
	MV1SetPosition(_modelHandle, pos.toVECTOR());
};
//----------------------------------------------------------------------
// @brief 正面方向を設定
// @param 正面方向
// @return 無し
//----------------------------------------------------------------------
void ModelBase::SetModelForwardRotationY(const Vector3D& forwardVec){
	Math::SetModelForward_RotationY(_modelHandle, forwardVec.toVECTOR());
};
//----------------------------------------------------------------------
// @brief モデルの拡大率を設定
// @param 拡大率
// @return 無し
//----------------------------------------------------------------------
void ModelBase::SetScale(const Vector3D& scale){
	MV1SetScale(_modelHandle, scale.toVECTOR());
};
//----------------------------------------------------------------------
// @brief モデルの回転値を設定
// @param 回転値
// @return 無し
//----------------------------------------------------------------------
void ModelBase::SetRotation(const Vector3D& rot){
	MV1SetRotationXYZ(_modelHandle, rot.toVECTOR());
};
//----------------------------------------------------------------------
// @brief モデルのアニメーションのブレンド率を設定
// @param アニメーションのインデックス
// @param ブレンド率
// @return 無し
//----------------------------------------------------------------------
void ModelBase::SetAttachAnimBlendRate(int attachIndex, float rate){
	MV1SetAttachAnimBlendRate(_modelHandle, attachIndex, rate);
};
//----------------------------------------------------------------------
// @brief モデルのアニメーションの時間を設定
// @param アニメーションのインデックス
// @param 時間
// @return 無し
//----------------------------------------------------------------------
void ModelBase::SetAttachAnimTime(int attachIndex, float time){
	MV1SetAttachAnimTime(_modelHandle, attachIndex, time);
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
void ModelBase::Render(){
	if(_isShader){
		// シェーダーを使用する
		MV1SetUseOrigShader(true);
		SetUsePixelShader(_pixelShader);
		SetUseVertexShader(_vertexShader);
	}
	// モデルの描画
	MV1DrawModel(_modelHandle);
	if (_isShader) {
		// シェーダーを使用しない
		MV1SetUseOrigShader(false);
	}
};
