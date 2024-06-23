
// マクロ定義 -----------------------------------

#define DX_D3D11_SHADER_FLOAT			float
#define DX_D3D11_SHADER_FLOAT2			float2
#define DX_D3D11_SHADER_FLOAT3			float3
#define DX_D3D11_SHADER_FLOAT4			float4

#define DX_D3D11_SHADER_INT				int
#define DX_D3D11_SHADER_INT2			int2
#define DX_D3D11_SHADER_INT3			int3
#define DX_D3D11_SHADER_INT4			int4

// 構造体定義 --------------------------------------------------------------------
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

// 定数バッファピクセルシェーダー基本パラメータ
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	DX_D3D11_SHADER_FLOAT4 FactorColor; // アルファ値等

	DX_D3D11_SHADER_FLOAT MulAlphaColor; // カラーにアルファ値を乗算するかどうか( 0.0f:乗算しない  1.0f:乗算する )
	DX_D3D11_SHADER_FLOAT AlphaTestRef; // アルファテストで使用する比較値
	DX_D3D11_SHADER_FLOAT2 Padding1;

	DX_D3D11_SHADER_INT AlphaTestCmpMode; // アルファテスト比較モード( DX_CMP_NEVER など )
	DX_D3D11_SHADER_INT NoLightAngleAttenuation; // ライトの角度減衰を行わないか( 0:減衰を行う   1:減衰を行わない )
	DX_D3D11_SHADER_INT2 Padding2;

	DX_D3D11_SHADER_FLOAT4 IgnoreTextureColor; // テクスチャカラー無視処理用カラー

	DX_D3D11_SHADER_FLOAT4 DrawAddColor; // 加算する色
};

// ピクセルシェーダー・頂点シェーダー共通パラメータ
struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT Light[6]; // ライトパラメータ
};

// 頂点シェーダー・ピクセルシェーダー共通パラメータ
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON g_Common;
};

// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_PS_BASE : register(b1)
{
    DX_D3D11_PS_CONST_BUFFER_BASE g_Base;
};

cbuffer Rimcolor : register(b10)
{
    float4 RimColor;
};

// ピクセルシェーダーの入力
struct PS_INPUT
{
    float4 Diffuse : COLOR0; // ディフューズカラー
    float4 Specular : COLOR1; // スペキュラカラー
    float2 TexCoords0 : TEXCOORD0; // テクスチャ座標とサブテクスチャ座標( x:テクスチャ座標x  y:テクスチャ座標)
    float3 VPosition : TEXCOORD1; // 頂点座標から視線へのベクトル( ビュー空間 )
    float3 Normal : TEXCOORD2; // x.y.z:法線( ビュー空間 ) 
    float3 NormalView : TEXCOORD3; // x.y.z:法線( ビュー空間 ) 
    float4 Position : SV_POSITION; // 座標( プロジェクション空間 )
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
    float4 Color0 : SV_TARGET0; // 色
};

SamplerState TextureSampler : register(s0);
Texture2D Texture : register(t0);

// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
    PS_OUTPUT PSOutput;
    float4 TextureDifColor;
    float rimPow1;
    float rimPow2;
    float4 emissive;
    TextureDifColor = Texture.Sample(TextureSampler, PSInput.TexCoords0);
    float3 normal = normalize(PSInput.Normal);
    float3 view = normalize(PSInput.NormalView);
     // リムライトのかかる部分を計算
    rimPow1 = 1.0f - max(0.0f, dot(g_Common.Light[0].Direction, normal));
    rimPow2 = 1.0f - max(0.0f, view.z * -1);
    // リムライトの強さ計算
    emissive.rgb = RimColor.rgb * pow(rimPow1 * rimPow2, 1.0f);
    emissive.a = 1.0f;
    // 元の色にリムライトを加算
    PSOutput.Color0 =TextureDifColor + emissive;
    PSOutput.Color0.a = PSInput.Diffuse.a * TextureDifColor.a * g_Base.FactorColor.a * emissive.a;

    return PSOutput;
}

