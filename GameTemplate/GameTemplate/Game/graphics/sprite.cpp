#include "stdafx.h"
#include "sprite.h"

namespace {
	struct SSinpleVertex
	{
		CVector4 pos;
		CVector2 tex;
	};
}
const CVector2  sprite::DEFAULT_PIVOT = { 0.5f,0.5f };
sprite::sprite()
{
}

sprite::~sprite()
{
}

void sprite::InitWorld2D(ShaderResourceView& tex, float w, float h)
{
	m_ps1.Load("Assets/shader/sprite.fx", "PS3DMain", Shader::EnType::PS);
	m_vs1.Load("Assets/shader/sprite.fx", "VS3DMain", Shader::EnType::VS);
	m_size.x = w;
	m_size.y = h;
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;

	SSinpleVertex vertices[4]=
	{
			{
				CVector4(-halfW,-halfH,0.0f,1.0f),
				CVector2(0.0f,1.0f),
			},
			{
				CVector4(halfW,-halfH,0.0f,1.0f),
				CVector2(1.0f,1.0f),
			},
			{
				CVector4(-halfW, halfH, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(halfW, halfH, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}
	};

	
	short indices[] = { 0,1,2,3 };

	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		4,
		sizeof(SSinpleVertex),
		vertices,
		4,
		IndexBuffer::enIndexType_16,
		indices
	);
	m_textureSRV = &tex;
	m_cb.Create(nullptr, sizeof(SSpriteCB));
}

void sprite::InitScreen2D(ShaderResourceView& tex, float w, float h,float size)
{
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	m_size.x = w;
	m_size.y = h;

	cb2D.trans.x = 0.0f;
	cb2D.trans.y = 0.0f;
	cb2D.trans.z = 0.0f;
	cb2D.trans.w = 0.0f;

	SSinpleVertex vertices[4] =
	{
			{
				CVector4(-1.0f*size+w,-1.0f*size+h,0.0f,1.0f),
				CVector2(0.0f,1.0f),
			},
			{
				CVector4(1.0f*size+w,-1.0f*size+h,0.0f,1.0f),
				CVector2(1.0f,1.0f),
			},
			{
				CVector4(-1.0f*size+w, 1.0f*size+h, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(1.0f*size+w, 1.0f*size+h, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}
	};


	short indices[] = { 0,1,2,3 };

	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		4,
		sizeof(SSinpleVertex),
		vertices,
		4,
		IndexBuffer::enIndexType_16,
		indices
	);
	m_textureSRV = &tex;
	m_cb2D.Create(nullptr, sizeof(SSpriteCB2D));
}

void sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
{
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//画像のハーフサイズを求める。
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(trans);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mPivotTrans, mScale);
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);
}

void sprite::Draw(ID3D11DeviceContext& rc, const CMatrix& viewMatrix, const CMatrix& projMatrix)
{
	if (m_textureSRV == nullptr) {
		throw;
		return;
	}
	SSpriteCB cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, viewMatrix);
	cb.WVP.Mul(cb.WVP, projMatrix);
	cb.mulColor = m_mulColor;

	rc.UpdateSubresource(m_cb.GetBody(),0,NULL,&cb,0,0);
	rc.VSSetConstantBuffers(0,1, &m_cb.GetBody());
	rc.PSSetConstantBuffers(0,1, &m_cb.GetBody());
	rc.PSSetShaderResources(0,1, &m_textureSRV->GetBody());
	rc.PSSetShader((ID3D11PixelShader*)m_ps1.GetBody(),NULL,0);
	rc.VSSetShader((ID3D11VertexShader*)m_vs1.GetBody(),NULL,0);
	rc.IASetInputLayout(m_vs1.GetInputLayout());
	m_primitive.Draw(rc);
}

void sprite::Update(const CVector2& trans)
{
	
	cb2D.trans.x = trans.x;
	cb2D.trans.y = trans.y;
	cb2D.trans.z = 0.0f;
	cb2D.trans.w = 0.0f;
}

void sprite::Draw(ID3D11DeviceContext& rc)
{
	if (m_textureSRV == nullptr) {
		throw;
		return;
	}

	cb2D.mulColor = m_mulColor;
	rc.UpdateSubresource(m_cb2D.GetBody(), 0, NULL, &cb2D, 0, 0);
	rc.VSSetConstantBuffers(11, 1, &m_cb2D.GetBody());
	rc.PSSetConstantBuffers(11, 1, &m_cb2D.GetBody());
	rc.PSSetShaderResources(0, 1, &m_textureSRV->GetBody());
	rc.PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	rc.VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	rc.IASetInputLayout(m_vs.GetInputLayout());
	m_primitive.Draw(rc);
}