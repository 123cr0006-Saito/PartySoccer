

// �}�N����` -----------------------------------

#define DX_D3D11_SHADER_FLOAT			float
#define DX_D3D11_SHADER_FLOAT2			float2
#define DX_D3D11_SHADER_FLOAT3			float3
#define DX_D3D11_SHADER_FLOAT4			float4

#define DX_D3D11_SHADER_INT			int
#define DX_D3D11_SHADER_INT2			int2
#define DX_D3D11_SHADER_INT3			int3
#define DX_D3D11_SHADER_INT4			int4

// �}�N����` -----------------------------------

#define DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM			3			// �e�N�X�`�����W�ϊ��s��̓]�u�s��̐�
#define DX_D3D11_VS_CONST_WORLD_MAT_NUM					54			// �g���C�A���O�����X�g��œ����Ɏg�p���郍�[�J�������[���h�s��̍ő吔

// �\���̒�` --------------------------------------------------------------------

// �}�e���A���p�����[�^
struct DX_D3D11_CONST_MATERIAL
{
	DX_D3D11_SHADER_FLOAT4 Diffuse; // �f�B�t���[�Y�J���[
	DX_D3D11_SHADER_FLOAT4 Specular; // �X�y�L�����J���[
	DX_D3D11_SHADER_FLOAT4 Ambient_Emissive; // �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[

	DX_D3D11_SHADER_FLOAT Power; // �X�y�L�����̋���
	DX_D3D11_SHADER_FLOAT TypeParam0; // �}�e���A���^�C�v�p�����[�^0
	DX_D3D11_SHADER_FLOAT TypeParam1; // �}�e���A���^�C�v�p�����[�^1
	DX_D3D11_SHADER_FLOAT TypeParam2; // �}�e���A���^�C�v�p�����[�^2
};

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

// �s�N�Z���V�F�[�_�[�E���_�V�F�[�_�[���ʃp�����[�^
struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT Light[6]; // ���C�g�p�����[�^
    DX_D3D11_CONST_MATERIAL Material; // �}�e���A���p�����[�^
};

// ��{�p�����[�^
struct DX_D3D11_VS_CONST_BUFFER_BASE
{
	DX_D3D11_SHADER_FLOAT4 AntiViewportMatrix[4]; // �A���`�r���[�|�[�g�s��
	DX_D3D11_SHADER_FLOAT4 ProjectionMatrix[4]; // �r���[�@���@�v���W�F�N�V�����s��
	DX_D3D11_SHADER_FLOAT4 ViewMatrix[3]; // ���[���h�@���@�r���[�s��
	DX_D3D11_SHADER_FLOAT4 LocalWorldMatrix[3]; // ���[�J���@���@���[���h�s��

	DX_D3D11_SHADER_FLOAT4 ToonOutLineSize; // �g�D�[���̗֊s���̑傫��
	DX_D3D11_SHADER_FLOAT DiffuseSource; // �f�B�t���[�Y�J���[( 0.0f:�}�e���A��  1.0f:���_ )
	DX_D3D11_SHADER_FLOAT SpecularSource; // �X�y�L�����J���[(   0.0f:�}�e���A��  1.0f:���_ )
	DX_D3D11_SHADER_FLOAT MulSpecularColor; // �X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )
	DX_D3D11_SHADER_FLOAT Padding;
};

// ���̑��̍s��
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX
{
	DX_D3D11_SHADER_FLOAT4 ShadowMapLightViewProjectionMatrix[3][4]; // �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
	DX_D3D11_SHADER_FLOAT4 TextureMatrix[DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM][2]; // �e�N�X�`�����W����p�s��
};

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
struct DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX
{
	DX_D3D11_SHADER_FLOAT4		Matrix[ DX_D3D11_VS_CONST_WORLD_MAT_NUM * 3 ] ;					// ���[�J���@���@���[���h�s��
};

// �f�[�^�^��` ---------------------------------


// ���_�V�F�[�_�[�E�s�N�Z���V�F�[�_�[���ʃp�����[�^
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON g_Common;
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_VS_BASE : register(b1)
{
    DX_D3D11_VS_CONST_BUFFER_BASE g_Base;
};

// ���̑��̍s��
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX : register(b2)
{
    DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX g_OtherMatrix;
};

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
cbuffer cbD3D11_CONST_BUFFER_VS_LOCALWORLDMATRIX : register(b3)
{
    DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX g_LocalWorldMatrix;
};


// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float3 Position        : POSITION ;			// ���W( ���[�J����� )
	float3 Normal          : NORMAL ;			// �@��( ���[�J����� )
	float4 Diffuse         : COLOR0 ;			// �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1 ;			// �X�y�L�����J���[
	float4 TexCoords0      : TEXCOORD0 ;		// �e�N�X�`�����W
	float4 TexCoords1      : TEXCOORD1 ;		// �T�u�e�N�X�`�����W

	// �X�L�j���O���b�V��
	int4   BlendIndices0   : BLENDINDICES0 ;	// �{�[�������p Float�^�萔�z��C���f�b�N�X�O
	float4 BlendWeight0    : BLENDWEIGHT0 ;		// �{�[�������p�E�G�C�g�l�O

} ;

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float4 Diffuse         : COLOR0 ;		// �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1 ;		// �X�y�L�����J���[
	float2 TexCoords0    : TEXCOORD0 ;	// �e�N�X�`�����W�ƃT�u�e�N�X�`�����W( x:�e�N�X�`�����Wx  y:�e�N�X�`�����Wy  z:�T�u�e�N�X�`�����Wx  w:�T�u�e�N�X�`�����Wy )

	float3 VPosition        : TEXCOORD1 ;	// ���_���W���王���ւ̃x�N�g��( �r���[��� )
	float3 Normal      : TEXCOORD2 ;	// x.y.z:�@��( �r���[��� )  w:�t�H�O�p�����[�^
	float3 NormalView : TEXCOORD3; // �@��( �r���[��� )
	float4 Position        : SV_POSITION ;	// ���W( �v���W�F�N�V������� )
} ;


// main�֐�
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

	// �X�L�����b�V��
	// �u�����h�s��̍쐬
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

	// ���[�J�����W�̃Z�b�g
	localPosition.xyz = VSInput.Position ;
	localPosition.w = 1.0f ;

	//--------------------------------------------------------------------------------------------
	// ���W�v�Z( ���[�J�������[���h���r���[���v���W�F�N�V���� )
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
	
	// ���[�J����Ԃ��烏�[���h��Ԃ֕ϊ�
    worldNorm.x = dot(VSInput.Normal,localWorldMatrix[0]);
    worldNorm.y = dot( VSInput.Normal,localWorldMatrix[1]);
    worldNorm.z = dot( VSInput.Normal,localWorldMatrix[2]);
	// ���[���h��Ԃ���r���[��Ԃ֕ϊ�
    viewNorm.x = mul(worldNorm,g_Base.ViewMatrix[0]);
    viewNorm.y = mul(worldNorm,g_Base.ViewMatrix[1]);
    viewNorm.z = mul(worldNorm,g_Base.ViewMatrix[2]);
	
    //���C�g�f�B�t���[�Y�J���[�ƃ��C�g�X�y�L�����J���[�̊p�x�����v�Z
	// �@���ƃ��C�g�̋t�����x�N�g���Ƃ̓��ς� lLightLitParam.x �ɃZ�b�g
    lightLitParam.x = dot(viewNorm, -g_Common.Light[0].Direction);

	// �n�[�t�x�N�g���̌v�Z norm( ( norm( ���_�ʒu���王�_�ւ̃x�N�g�� ) + ���C�g�̕��� ) )
    lightHalfVec = normalize(normalize(-viewPosition.xyz) - g_Common.Light[0].Direction);

	// �@���ƃn�[�t�x�N�g���̓��ς� lLightLitParam.y �ɃZ�b�g
    lightLitParam.y = dot(lightHalfVec, viewNorm);

	// �X�y�L�������˗��� lLightLitParam.w �ɃZ�b�g
    lightLitParam.w = g_Common.Material.Power;

	// ���C�g�p�����[�^�v�Z
    lightLitDest = lit(lightLitParam.x, lightLitParam.y, lightLitParam.w);
	
	// �f�B�q���[�Y�J���[��ݒ�
    VSOutput.Diffuse.xyz = lightLitDest.y * g_Common.Light[0].Diffuse * g_Common.Material.Diffuse.xyz + g_Common.Light[0].Ambient.xyz + g_Common.Material.Ambient_Emissive.xyz;

	// �f�B�t���[�Y�A���t�@�̓}�e���A���̃f�B�t���[�Y�J���[�̃A���t�@�����̂܂܎g��
    VSOutput.Diffuse.w = g_Common.Material.Diffuse.w;

	// �X�y�L�����J���[��ݒ�
    VSOutput.Specular.xyz = lightLitDest.z * g_Common.Light[0].Specular * g_Common.Material.Specular.xyz;

	// �X�y�L�����A���t�@�̓}�e���A���̃X�y�L�����J���[�̃A���t�@�����̂܂܎g��
    VSOutput.Specular.w = g_Common.Material.Specular.w;
	
	// �e�N�X�`�����W�̃Z�b�g
    VSOutput.TexCoords0.x = dot(VSInput.TexCoords0, g_OtherMatrix.TextureMatrix[0][0]);
    VSOutput.TexCoords0.y = dot(VSInput.TexCoords0, g_OtherMatrix.TextureMatrix[0][1]);
	
    VSOutput.Normal = worldNorm;
    VSOutput.NormalView = viewNorm;

	return VSOutput ;
}

