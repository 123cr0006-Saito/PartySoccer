//----------------------------------------------------------------------
// @filename RimLightModel.cpp
// @author: saito ko
// @explanation
// モデル描画にリムライトを使用するクラス
//----------------------------------------------------------------------
#include "../../Header/Model/RimLightModel.h"
#include "../AppFrame/source/System/Header/Resource/ResourceServer.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param モデルの名前
// @param レイヤー番号
// @param モデルハンドル
// @return 無し
//----------------------------------------------------------------------
RimLightModel::RimLightModel(std::string name, int layer, int handle) :
	ModelBase(name,layer,handle)
{
	_pixelShader = ResourceServer::LoadPixelShader("RimLightPS","Shader/PS/MV1_Rim_PS.pso");
	_vertexShader = ResourceServer::LoadVertexShader("RimLightVS","Shader/VS/MV1_VS.vso");
	_rimLightColor = CreateShaderConstantBuffer(sizeof(float) * 4);
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
RimLightModel::~RimLightModel(){
	DeleteShaderConstantBuffer(_rimLightColor);
};
//----------------------------------------------------------------------
// @brief リムライトの色を設定
// @param r 赤値
// @param g 緑値
// @param b 青値
// @return 無し
//----------------------------------------------------------------------
void RimLightModel::SetRimColor(float r, float g, float b){
	FLOAT4* color = (FLOAT4*)GetBufferShaderConstantBuffer(_rimLightColor);
	color->x = r;
	color->y = g;
	color->z = b;
	color->w = 1.0f;
	UpdateShaderConstantBuffer(_rimLightColor);
	SetShaderConstantBuffer(_rimLightColor, DX_SHADERTYPE_PIXEL, 10);
};
