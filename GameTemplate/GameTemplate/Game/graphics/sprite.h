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

	void InitWorld2D(ShaderResourceView& tex, float w, float h);			//èâä˙âª
	void InitScreen2D(ShaderResourceView& tex, float w, float h,float size);

	void SetTexture(ShaderResourceView& tex)							//
	{
		m_textureSRV = &tex;
	}

	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}

	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
	void Update(const CVector2& trans);
	void Draw(ID3D11DeviceContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix);
	void Draw(ID3D11DeviceContext& renderContext);
private:
	struct SSpriteCB {
		CMatrix WVP;
		CVector4 mulColor;
	};
	struct SSpriteCB2D {
		CVector4 trans;
		CVector4 mulColor;
	};

	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	CMatrix m_world = CMatrix::Identity();
	Shader m_ps;
	Shader m_vs;
	Shader m_ps1;
	Shader m_vs1;


	SSpriteCB2D cb2D;
	CVector4 m_mulColor = CVector4::White();
	Primitive m_primitive;
	ShaderResourceView* m_textureSRV = nullptr;
	ConstantBuffer m_cb;
	ConstantBuffer m_cb2D;

	CVector2 m_size = CVector2::Zero();
};

