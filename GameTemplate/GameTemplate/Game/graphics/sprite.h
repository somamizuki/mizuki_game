#pragma once
#include"ShaderResourceView.h"
#include"UnorderedAccessView.h"
#include"Primitive.h"
#include"ConstantBuffer.h"
#include"StructuredBuffer.h"

class sprite:Noncopyable
{
public:
	static const CVector2 DEFAULT_PIVOT;
	sprite();
	~sprite();

	void Init(ID3D11ShaderResourceView* tex, float w, float h);
	void FullScreenInit();
	void Release();
	void SetShader(const char* filepathVS, const char* filepathPS)
	{
		m_ps.Load(filepathPS, "PSMain", Shader::EnType::PS);
		m_vs.Load(filepathVS, "VSMain", Shader::EnType::VS);
	}
	void SetShader(Shader* VS, Shader* PS)
	{
		m_ps = *PS;
		m_vs = *VS;
	}
	void SetTexture(ID3D11ShaderResourceView* tex)							//
	{
		m_textureSRV = tex;
	}

	void SetViewProj(CMatrix& viewM,CMatrix& projM)
	{
		m_view = viewM;
		m_proj = projM;
	}
	void SetProj(CMatrix& projM)
	{
		m_proj = projM;
	}

	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}

	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
	void Draw(ID3D11DeviceContext& renderContext);
	void PostEffectDraw(ID3D11DeviceContext& renderContext);
private:
	struct SSpriteCB {
		CMatrix WVP;
		CVector4 mulColor;
	};
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	CMatrix m_world = CMatrix::Identity();
	Shader m_ps;
	Shader m_vs;
	CVector4 m_mulColor = CVector4::White();
	Primitive m_primitive;
	ID3D11ShaderResourceView* m_textureSRV = nullptr;
	ConstantBuffer m_cb;
	ID3D11SamplerState* m_samplerState = nullptr;
	CVector2 m_size = CVector2::Zero();

	CMatrix m_view;
	CMatrix m_proj;
	bool f_update = false;
};

