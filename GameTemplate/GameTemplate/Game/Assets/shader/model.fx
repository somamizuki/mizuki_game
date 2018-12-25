/*!
 * @brief	���f���V�F�[�_�[�B
 */

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	

TextureCube<float4> skyCubeMap : register(t0);	//�X�J�C�L���[�u�}�b�v�B
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);

Texture2D<float4> shadowMap : register(t2);		//todo �V���h�E�}�b�v�B

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer directionSum : register(b1) {
	int dirsum;
};

cbuffer pointSum : register(b2) {
	int pointsum;
};

cbuffer spotSum : register(b3) {
	int spotsum;
};

cbuffer SMCb:register(b4)
{
	//todo ���C�g�r���[�s���ǉ��B
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
}

cbuffer lightparam : register(b10)
{
	float4 eyepos;
	float specPow;
}


struct SDirectionLight {
	float4 Dir_color;
	float4 Dir_direction;
};

struct SPointLight {
	float4 Point_color;
	float4 Point_position;
	float Point_range;
};

struct SSpotLight {
	float4 Spot_color;
	float4 Spot_position;
	float4 Spot_direction;
	float  Spot_angle;
	float Spot_range;
};



StructuredBuffer <SDirectionLight>DirectionLightSB:register(t100);
StructuredBuffer <SPointLight>PointLightSB : register(t101);
StructuredBuffer <SSpotLight>SpotLightSB : register(t102);


/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;
	float4 posInLVP		: TEXCOORD2;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
};

struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//���W�B
};

/*
���C�g�̌v�Z
*/
//�f�B���N�V����
float4 DirectionLightColor(PSInput Input)
{
	float4 finalcolor = { 0.0f,0.0f,0.0f,0.0f };
	
	float3 toEyeV = normalize(Input.worldPos-eyepos);
	float3 reflecteyedir = reflect(toEyeV, Input.Normal);//-toEyeV + 2 * dot(Input.Normal, toEyeV)*Input.Normal;
	float t = 0.0f;
	float4 specLig = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < dirsum; i++)
	{
		
		float3 m_d2 = normalize(DirectionLightSB[i].Dir_direction);


		float4 DlightC = max(0, dot(-m_d2, Input.Normal)) * DirectionLightSB[i].Dir_color;

		t = max(0.0f, dot(m_d2*-1.0f, reflecteyedir));
		specLig = max(0.0f,pow(t, specPow) * DirectionLightSB[i].Dir_color);
		DlightC += specLig;
		finalcolor += max(0.0f, DlightC);
		
	}
	return finalcolor;
}
//�|�C���g
float4 PointLightColor(PSInput Input)
{
	float4 finalcolor = { 0.0f,0.0f,0.0f,0.0f };
	float3 toEyeV = normalize(Input.worldPos-eyepos);
	float3 reflecteyedir = reflect(toEyeV, Input.Normal);//-toEyeV + 2 * dot(Input.Normal, toEyeV)*Input.Normal;
	float t = 0.0f;
	float4 specLig = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < pointsum; i++)
	{

		float3 pointLightV = Input.worldPos - PointLightSB[i].Point_position;
		pointLightV = normalize(pointLightV);
		float4 pointlightC = max(0.0f, dot(-pointLightV, Input.Normal)) * PointLightSB[i].Point_color;
		
		t = max(0.0f, dot(pointLightV*-1.0f, reflecteyedir));
		specLig = max(0.0f, pow(t, specPow) * PointLightSB[i].Point_color);
		pointlightC += specLig;

		pointlightC = pointlightC * max(0.0f, (1.0f - (length(Input.worldPos - PointLightSB[i].Point_position) / PointLightSB[i].Point_range)));
		
		

		finalcolor += max(0.0f, pointlightC);
	}

	return finalcolor;
}

float4 PostPointLightColor(PSInput Input)
{
	float4 finalcolor = { 0.0f,0.0f,0.0f,0.0f };
	for (int i = 0; i < pointsum; i++)
	{

		float3 pointLightV = Input.worldPos - PointLightSB[i].Point_position;
		pointLightV = normalize(pointLightV);
		float4 pointlightC = max(0.0f, dot(pointLightV, Input.Normal)) * PointLightSB[i].Point_color;
		finalcolor += max(0.0f, pointlightC);
	}

	return finalcolor;
}


//�X�|�b�g
float4 SpotLightColor(PSInput Input)
{
	
	float4 finalcolor = { 0.0f,0.0f,0.0f,0.0f };
	float3 toEyeV = normalize(Input.worldPos-eyepos);
	float3 reflecteyedir = reflect(toEyeV, Input.Normal);//-toEyeV + 2 * dot(Input.Normal, toEyeV)*Input.Normal;
	float t = 0.0f;
	float4 specLig = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < spotsum; i++)
	{
		
		float3 spotLightV = Input.worldPos - SpotLightSB[i].Spot_position;
		spotLightV = normalize(spotLightV);
		float4 spotlightC = max(0, dot(-spotLightV, Input.Normal))*SpotLightSB[i].Spot_color;

		float3 outV = Input.worldPos - SpotLightSB[i].Spot_position;
		float angle = acos(dot(normalize(SpotLightSB[i].Spot_direction), normalize(outV)));

		spotlightC = spotlightC * step(degrees(angle), SpotLightSB[i].Spot_angle);

		t = max(0.0f, dot(spotLightV*-1.0f, reflecteyedir));
		specLig = max(0.0f, pow(t, specPow) * SpotLightSB[i].Spot_color);
		spotlightC += specLig;

		spotlightC = spotlightC * max(0.0f, (1.0f - (length(Input.worldPos - SpotLightSB[i].Spot_position) / SpotLightSB[i].Spot_range)));
		


		

		finalcolor += max(0.0f, spotlightC);
	}

	

	return finalcolor;
}


/*!
 *@brief	�X�L���s����v�Z�B
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	psInput.worldPos = pos.xyz;
	float4 WorldPos = float4(psInput.worldPos.xyz, pos.w);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;


	if (isShadowReciever == 1) {
		//���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, WorldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	    pos = mul(skinning, In.Position);
	}
	psInput.worldPos = pos.xyz;
	float4 WorldPos = float4(psInput.worldPos.xyz, pos.w);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;


	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, WorldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{

	float4 texC = albedoTexture.Sample(Sampler ,In.TexCoord);
	
	return texC;
}

float4 PS2Main(PSInput In):SV_Target0
{
	float ligmin = 0.2f;
	float4 lig = DirectionLightColor(In) + PointLightColor(In) + /*SpotLightColor(In) + */float4(ligmin, ligmin, ligmin, 0.0f);

	float4 texC2 = albedoTexture.Sample(Sampler ,In.TexCoord);



	if (isShadowReciever == 1) {	//�V���h�E���V�[�o�[�B
		//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {

			///LVP��Ԃł̐[�x�l���v�Z�B
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
			float zInShadowMap = shadowMap.Sample(Sampler, shadowMapUV);

			if (zInLVP > zInShadowMap+0.00005f) {
				//�e�������Ă���̂ŁA�����キ����
				lig *= ligmin;
			}
		}
	}

	float4 texC = texC2 *lig;
	texC.w = 1.0f;

	return texC;
}

float4 PS3Main(PSInput In) :SV_Target0
{
	float4 texC = albedoTexture.Sample(Sampler ,In.TexCoord);
	float4 lig = PostPointLightColor(In);// +float4(0.1f, 0.1f, 0.1f, 0.0f);
	texC = texC * lig;
	return texC;
}

float4 PSCubeMain(PSInput In) : SV_Target0
{
	float4 color = skyCubeMap.Sample(Sampler, In.Normal*-1.0f);
	return color;
}

PSInput_ShadowMap VSShadowMapMain(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

float4 PSShadowMapMain(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}