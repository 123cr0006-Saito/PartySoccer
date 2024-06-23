
// �}�N����` -----------------------------------

#define DX_D3D11_SHADER_FLOAT			float
#define DX_D3D11_SHADER_FLOAT2			float2
#define DX_D3D11_SHADER_FLOAT3			float3
#define DX_D3D11_SHADER_FLOAT4			float4

#define DX_D3D11_SHADER_INT				int
#define DX_D3D11_SHADER_INT2			int2
#define DX_D3D11_SHADER_INT3			int3
#define DX_D3D11_SHADER_INT4			int4

// �\���̒�` --------------------------------------------------------------------
// ���C�g�p�����[�^
struct DX_D3D11_CONST_LIGHT
{
    int Type; // ���C�g�^�C�v( DX_LIGHTTYPE_POINT �Ȃ� )
    int3 Padding1; // �p�f�B���O�P

    float3 Position; // ���W( �r���[��� )
    float RangePow2; // �L�������̂Q��

    float3 Direction; // ����( �r���[��� )
    float FallOff; // �X�|�b�g���C�g�pFallOff

    float3 Diffuse; // �f�B�t���[�Y�J���[
    float SpotParam0; // �X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) )

    float3 Specular; // �X�y�L�����J���[
    float SpotParam1; // �X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

    float4 Ambient; // �A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������

    float Attenuation0; // �����ɂ�錸�������p�p�����[�^�O
    float Attenuation1; // �����ɂ�錸�������p�p�����[�^�P
    float Attenuation2; // �����ɂ�錸�������p�p�����[�^�Q
    float Padding2; // �p�f�B���O�Q
};

// �萔�o�b�t�@�s�N�Z���V�F�[�_�[��{�p�����[�^
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	DX_D3D11_SHADER_FLOAT4 FactorColor; // �A���t�@�l��

	DX_D3D11_SHADER_FLOAT MulAlphaColor; // �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0f:��Z���Ȃ�  1.0f:��Z���� )
	DX_D3D11_SHADER_FLOAT AlphaTestRef; // �A���t�@�e�X�g�Ŏg�p�����r�l
	DX_D3D11_SHADER_FLOAT2 Padding1;

	DX_D3D11_SHADER_INT AlphaTestCmpMode; // �A���t�@�e�X�g��r���[�h( DX_CMP_NEVER �Ȃ� )
	DX_D3D11_SHADER_INT NoLightAngleAttenuation; // ���C�g�̊p�x�������s��Ȃ���( 0:�������s��   1:�������s��Ȃ� )
	DX_D3D11_SHADER_INT2 Padding2;

	DX_D3D11_SHADER_FLOAT4 IgnoreTextureColor; // �e�N�X�`���J���[���������p�J���[

	DX_D3D11_SHADER_FLOAT4 DrawAddColor; // ���Z����F
};

// �s�N�Z���V�F�[�_�[�E���_�V�F�[�_�[���ʃp�����[�^
struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT Light[6]; // ���C�g�p�����[�^
};

// ���_�V�F�[�_�[�E�s�N�Z���V�F�[�_�[���ʃp�����[�^
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON g_Common;
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_BASE : register(b1)
{
    DX_D3D11_PS_CONST_BUFFER_BASE g_Base;
};

cbuffer Rimcolor : register(b10)
{
    float4 RimColor;
};

// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
    float4 Specular : COLOR1; // �X�y�L�����J���[
    float2 TexCoords0 : TEXCOORD0; // �e�N�X�`�����W�ƃT�u�e�N�X�`�����W( x:�e�N�X�`�����Wx  y:�e�N�X�`�����W)
    float3 VPosition : TEXCOORD1; // ���_���W���王���ւ̃x�N�g��( �r���[��� )
    float3 Normal : TEXCOORD2; // x.y.z:�@��( �r���[��� ) 
    float3 NormalView : TEXCOORD3; // x.y.z:�@��( �r���[��� ) 
    float4 Position : SV_POSITION; // ���W( �v���W�F�N�V������� )
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
    float4 Color0 : SV_TARGET0; // �F
};

SamplerState TextureSampler : register(s0);
Texture2D Texture : register(t0);

// main�֐�
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
     // �������C�g�̂����镔�����v�Z
    rimPow1 = 1.0f - max(0.0f, dot(g_Common.Light[0].Direction, normal));
    rimPow2 = 1.0f - max(0.0f, view.z * -1);
    // �������C�g�̋����v�Z
    emissive.rgb = RimColor.rgb * pow(rimPow1 * rimPow2, 1.0f);
    emissive.a = 1.0f;
    // ���̐F�Ƀ������C�g�����Z
    PSOutput.Color0 =TextureDifColor + emissive;
    PSOutput.Color0.a = PSInput.Diffuse.a * TextureDifColor.a * g_Base.FactorColor.a * emissive.a;

    return PSOutput;
}

