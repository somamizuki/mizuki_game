cbuffer cb:register(b0) {
	float4x4 mvp;
	float4 mulColor;
};
struct VSInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORDO;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORDO;
};

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = In.pos;//mul(mvp, In.pos);
	psIn.uv = In.uv;
	return psIn;
}

PSInput VS3DMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = mul(mvp, In.pos);
	psIn.uv = In.uv;
	return psIn;
}

float4 PSMain(PSInput In) : SV_Target0
{
	return  colorTexture.Sample(Sampler,In.uv) * mulColor;
}
float4 PS3DMain(PSInput In) : SV_Target0
{
	return colorTexture.Sample(Sampler,In.uv) * mulColor;
}