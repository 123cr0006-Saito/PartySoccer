

// マクロ定義 -----------------------------------

#define DX_D3D11_SHADER_FLOAT			float
#define DX_D3D11_SHADER_FLOAT2			float2
#define DX_D3D11_SHADER_FLOAT3			float3
#define DX_D3D11_SHADER_FLOAT4			float4

#define DX_D3D11_SHADER_INT			int
#define DX_D3D11_SHADER_INT2			int2
#define DX_D3D11_SHADER_INT3			int3
#define DX_D3D11_SHADER_INT4			int4

// マクロ定義 -----------------------------------

#define DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM			3			// テクスチャ座標変換行列の転置行列の数
#define DX_D3D11_VS_CONST_WORLD_MAT_NUM					54			// トライアングルリスト一つで同時に使用するローカル→ワールド行列の最大数

// 構造体定義 --------------------------------------------------------------------

// マテリアルパラメータ
struct DX_D3D11_CONST_MATERIAL
{
	DX_D3D11_SHADER_FLOAT4 Diffuse; // ディフューズカラー
	DX_D3D11_SHADER_FLOAT4 Specular; // スペキュラカラー
	DX_D3D11_SHADER_FLOAT4 Ambient_Emissive; // マテリアルエミッシブカラー + マテリアルアンビエントカラー * グローバルアンビエントカラー

	DX_D3D11_SHADER_FLOAT Power; // スペキュラの強さ
	DX_D3D11_SHADER_FLOAT TypeParam0; // マテリアルタイプパラメータ0
	DX_D3D11_SHADER_FLOAT TypeParam1; // マテリアルタイプパラメータ1
	DX_D3D11_SHADER_FLOAT TypeParam2; // マテリアルタイプパラメータ2
};

// ライトパラメータ
struct DX_D3D11_CONST_LIGHT
{
    int Type; // ライトタイプ( DX_LIGHTTYPE_POINT など )
    int3 Padding1; // パディング１

    float3 Position; // 座標( ビュー空間 )
    float RangePow2; // 有効距離の２乗

    float3 Direction; // 方向( ビュー空間 )
    float FallOff; // スポットライト用FallOff

    float3 Diffuse; // ディフューズカラー
    float SpotParam0; // スポットライト用パラメータ０( cos( Phi / 2.0f ) )

    float3 Specular; // スペキュラカラー
    float SpotParam1; // スポットライト用パラメータ１( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

    float4 Ambient; // アンビエントカラーとマテリアルのアンビエントカラーを乗算したもの

    float Attenuation0; // 距離による減衰処理用パラメータ０
    float Attenuation1; // 距離による減衰処理用パラメータ１
    float Attenuation2; // 距離による減衰処理用パラメータ２
    float Padding2; // パディング２
};

// ピクセルシェーダー・頂点シェーダー共通パラメータ
struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT Light[6]; // ライトパラメータ
    DX_D3D11_CONST_MATERIAL Material; // マテリアルパラメータ
};

// 基本パラメータ
struct DX_D3D11_VS_CONST_BUFFER_BASE
{
	DX_D3D11_SHADER_FLOAT4 AntiViewportMatrix[4]; // アンチビューポート行列
	DX_D3D11_SHADER_FLOAT4 ProjectionMatrix[4]; // ビュー　→　プロジェクション行列
	DX_D3D11_SHADER_FLOAT4 ViewMatrix[3]; // ワールド　→　ビュー行列
	DX_D3D11_SHADER_FLOAT4 LocalWorldMatrix[3]; // ローカル　→　ワールド行列

	DX_D3D11_SHADER_FLOAT4 ToonOutLineSize; // トゥーンの輪郭線の大きさ
	DX_D3D11_SHADER_FLOAT DiffuseSource; // ディフューズカラー( 0.0f:マテリアル  1.0f:頂点 )
	DX_D3D11_SHADER_FLOAT SpecularSource; // スペキュラカラー(   0.0f:マテリアル  1.0f:頂点 )
	DX_D3D11_SHADER_FLOAT MulSpecularColor; // スペキュラカラー値に乗算する値( スペキュラ無効処理で使用 )
	DX_D3D11_SHADER_FLOAT Padding;
};

// その他の行列
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX
{
	DX_D3D11_SHADER_FLOAT4 ShadowMapLightViewProjectionMatrix[3][4]; // シャドウマップ用のライトビュー行列とライト射影行列を乗算したもの
	DX_D3D11_SHADER_FLOAT4 TextureMatrix[DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM][2]; // テクスチャ座標操作用行列
};

// スキニングメッシュ用の　ローカル　→　ワールド行列
struct DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX
{
	DX_D3D11_SHADER_FLOAT4		Matrix[ DX_D3D11_VS_CONST_WORLD_MAT_NUM * 3 ] ;					// ローカル　→　ワールド行列
};

// データ型定義 ---------------------------------


// 頂点シェーダー・ピクセルシェーダー共通パラメータ
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON g_Common;
};

// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_VS_BASE : register(b1)
{
    DX_D3D11_VS_CONST_BUFFER_BASE g_Base;
};

// その他の行列
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX : register(b2)
{
    DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX g_OtherMatrix;
};

// スキニングメッシュ用の　ローカル　→　ワールド行列
cbuffer cbD3D11_CONST_BUFFER_VS_LOCALWORLDMATRIX : register(b3)
{
    DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX g_LocalWorldMatrix;
};


// 頂点シェーダーの入力
struct VS_INPUT
{
	float3 Position        : POSITION ;			// 座標( ローカル空間 )
	float3 Normal          : NORMAL ;			// 法線( ローカル空間 )
	float4 Diffuse         : COLOR0 ;			// ディフューズカラー
	float4 Specular        : COLOR1 ;			// スペキュラカラー
	float4 TexCoords0      : TEXCOORD0 ;		// テクスチャ座標
	float4 TexCoords1      : TEXCOORD1 ;		// サブテクスチャ座標

	// スキニングメッシュ
	int4   BlendIndices0   : BLENDINDICES0 ;	// ボーン処理用 Float型定数配列インデックス０
	float4 BlendWeight0    : BLENDWEIGHT0 ;		// ボーン処理用ウエイト値０

} ;

// 頂点シェーダーの出力
struct VS_OUTPUT
{
	float4 Diffuse         : COLOR0 ;		// ディフューズカラー
	float4 Specular        : COLOR1 ;		// スペキュラカラー
	float2 TexCoords0    : TEXCOORD0 ;	// テクスチャ座標とサブテクスチャ座標( x:テクスチャ座標x  y:テクスチャ座標y  z:サブテクスチャ座標x  w:サブテクスチャ座標y )

	float3 VPosition        : TEXCOORD1 ;	// 頂点座標から視線へのベクトル( ビュー空間 )
	float3 Normal      : TEXCOORD2 ;	// x.y.z:法線( ビュー空間 )  w:フォグパラメータ
	float3 NormalView : TEXCOORD3; // 法線( ビュー空間 )
	float4 Position        : SV_POSITION ;	// 座標( プロジェクション空間 )
} ;


// main関数
VS_OUTPUT main( VS_INPUT VSInput )
{
	VS_OUTPUT	VSOutput ;
	int4			boneFloatIndex ;
	float4		localWorldMatrix[ 3 ] ;
	float4		localPosition ;
	float4		worldPosition ;
	float4		viewPosition ;
    float3		worldNorm;
    float3		viewNorm;
    float3		lightHalfVec;
    float4		lightLitParam;
    float4		lightLitDest;

	// スキンメッシュ
	// ブレンド行列の作成
	boneFloatIndex = VSInput.BlendIndices0 ;
    localWorldMatrix[ 0 ]  = g_LocalWorldMatrix.Matrix[ boneFloatIndex.x + 0 ] * VSInput.BlendWeight0.xxxx;
	localWorldMatrix[ 1 ]  = g_LocalWorldMatrix.Matrix[ boneFloatIndex.x + 1 ] * VSInput.BlendWeight0.xxxx;
	localWorldMatrix[ 2 ]  = g_LocalWorldMatrix.Matrix[ boneFloatIndex.x + 2 ] * VSInput.BlendWeight0.xxxx;

	localWorldMatrix[ 0 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.y + 0 ] * VSInput.BlendWeight0.yyyy;
	localWorldMatrix[ 1 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.y + 1 ] * VSInput.BlendWeight0.yyyy;
	localWorldMatrix[ 2 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.y + 2 ] * VSInput.BlendWeight0.yyyy;

	localWorldMatrix[ 0 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.z + 0 ] * VSInput.BlendWeight0.zzzz;
	localWorldMatrix[ 1 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.z + 1 ] * VSInput.BlendWeight0.zzzz;
	localWorldMatrix[ 2 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.z + 2 ] * VSInput.BlendWeight0.zzzz;

	localWorldMatrix[ 0 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.w + 0 ] * VSInput.BlendWeight0.wwww;
	localWorldMatrix[ 1 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.w + 1 ] * VSInput.BlendWeight0.wwww;
	localWorldMatrix[ 2 ] += g_LocalWorldMatrix.Matrix[ boneFloatIndex.w + 2 ] * VSInput.BlendWeight0.wwww;

	// ローカル座標のセット
	localPosition.xyz = VSInput.Position ;
	localPosition.w = 1.0f ;

	//--------------------------------------------------------------------------------------------
	// 座標計算( ローカル→ワールド→ビュー→プロジェクション )
	worldPosition.x = dot( localPosition, localWorldMatrix[ 0 ] ) ;
	worldPosition.y = dot( localPosition, localWorldMatrix[ 1 ] ) ;
	worldPosition.z = dot( localPosition, localWorldMatrix[ 2 ] ) ;
	worldPosition.w = 1.0f ;

	viewPosition.x = dot( worldPosition, g_Base.ViewMatrix[ 0 ] ) ;
	viewPosition.y = dot( worldPosition, g_Base.ViewMatrix[ 1 ] ) ;
	viewPosition.z = dot( worldPosition, g_Base.ViewMatrix[ 2 ] ) ;
	viewPosition.w = 1.0f ;

	VSOutput.Position.x  = dot( viewPosition, g_Base.ProjectionMatrix[ 0 ] ) ;
	VSOutput.Position.y  = dot( viewPosition, g_Base.ProjectionMatrix[ 1 ] ) ;
	VSOutput.Position.z  = dot( viewPosition, g_Base.ProjectionMatrix[ 2 ] ) ;
	VSOutput.Position.w = dot( viewPosition, g_Base.ProjectionMatrix[ 3 ] ) ;

    VSOutput.VPosition = viewPosition.xyz;
	//--------------------------------------------------------------------------------------------
	
	// ローカル空間からワールド空間へ変換
    worldNorm.x = dot(VSInput.Normal,localWorldMatrix[0]);
    worldNorm.y = dot( VSInput.Normal,localWorldMatrix[1]);
    worldNorm.z = dot( VSInput.Normal,localWorldMatrix[2]);
	// ワールド空間からビュー空間へ変換
    viewNorm.x = mul(worldNorm,g_Base.ViewMatrix[0]);
    viewNorm.y = mul(worldNorm,g_Base.ViewMatrix[1]);
    viewNorm.z = mul(worldNorm,g_Base.ViewMatrix[2]);
	
    //ライトディフューズカラーとライトスペキュラカラーの角度減衰計算
	// 法線とライトの逆方向ベクトルとの内積を lLightLitParam.x にセット
    lightLitParam.x = dot(viewNorm, -g_Common.Light[0].Direction);

	// ハーフベクトルの計算 norm( ( norm( 頂点位置から視点へのベクトル ) + ライトの方向 ) )
    lightHalfVec = normalize(normalize(-viewPosition.xyz) - g_Common.Light[0].Direction);

	// 法線とハーフベクトルの内積を lLightLitParam.y にセット
    lightLitParam.y = dot(lightHalfVec, viewNorm);

	// スペキュラ反射率を lLightLitParam.w にセット
    lightLitParam.w = g_Common.Material.Power;

	// ライトパラメータ計算
    lightLitDest = lit(lightLitParam.x, lightLitParam.y, lightLitParam.w);
	
	// ディヒューズカラーを設定
    VSOutput.Diffuse.xyz = lightLitDest.y * g_Common.Light[0].Diffuse * g_Common.Material.Diffuse.xyz + g_Common.Light[0].Ambient.xyz + g_Common.Material.Ambient_Emissive.xyz;

	// ディフューズアルファはマテリアルのディフューズカラーのアルファをそのまま使う
    VSOutput.Diffuse.w = g_Common.Material.Diffuse.w;

	// スペキュラカラーを設定
    VSOutput.Specular.xyz = lightLitDest.z * g_Common.Light[0].Specular * g_Common.Material.Specular.xyz;

	// スペキュラアルファはマテリアルのスペキュラカラーのアルファをそのまま使う
    VSOutput.Specular.w = g_Common.Material.Specular.w;
	
	// テクスチャ座標のセット
    VSOutput.TexCoords0.x = dot(VSInput.TexCoords0, g_OtherMatrix.TextureMatrix[0][0]);
    VSOutput.TexCoords0.y = dot(VSInput.TexCoords0, g_OtherMatrix.TextureMatrix[0][1]);
	
    VSOutput.Normal = worldNorm;
    VSOutput.NormalView = viewNorm;

	return VSOutput ;
}

