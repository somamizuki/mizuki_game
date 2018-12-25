/*!
 * @brief	モデルシェーダー。
 */

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	

TextureCube<float4> skyCubeMap : register(t0);	//スカイキューブマップ。
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

Texture2D<float4> shadowMap : register(t2);		//todo シャドウマップ。

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
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
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
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
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};

struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};

/*
ライトの計算
*/
//ディレクション
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
//ポイント
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


//スポット
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
 *@brief	スキン行列を計算。
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
 * @brief	スキンなしモデル用の頂点シェーダー。
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
		//ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, WorldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
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
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, WorldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
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



	if (isShadowReciever == 1) {	//シャドウレシーバー。
		//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {

			///LVP空間での深度値を計算。
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = shadowMap.Sample(Sampler, shadowMapUV);

			if (zInLVP > zInShadowMap+0.00005f) {
				//影が落ちているので、光を弱くする
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
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}