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
	m_view.MakeLookAt(
		{0.0f,0.0f,-0.01f},
		CVector3::Zero(),
		CVector3::Up()
	);
	m_proj.MakeOrthoProjectionMatrix(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		0.009f,
		0.015f
	);
	
}

sprite::~sprite()
{
	Release();
}
void sprite::Release()
{
	m_primitive.Release();
	m_textureSRV->Release();
	m_cb.Release();
	m_ps.Release();
	m_vs.Release();
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
}
void sprite::Init(ID3D11ShaderResourceView* tex, float w, float h)
{
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	m_size.x = w;
	m_size.y = h;
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;

	SSinpleVertex vertices[] =
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

	m_textureSRV = tex;
	m_cb.Create(nullptr, sizeof(SSpriteCB));

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void sprite::FullScreenInit()
{
	//デフォルトのシェーダー
	m_ps.Load("Assets/shader/sprite.fx", "PSPostEffectMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "PEVSMain", Shader::EnType::VS);

	SSinpleVertex vertices[] =
	{
			{
				CVector4(-1.0f,-1.0f,0.0f,1.0f),
				CVector2(0.0f,1.0f),
			},
			{
				CVector4(1.0f,-1.0f,0.0f,1.0f),
				CVector2(1.0f,1.0f),
			},
			{
				CVector4(-1.0f, 1.0f, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(1.0f, 1.0f, 0.0f, 1.0f),
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
}

void sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
{
	//ピボットを考慮に入れた平行移動行列を作成。
		//ピボットは真ん中が0.0, 0.0、左上が-1.0f, -1.0、右下が1.0、1.0になるようにする。
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
	f_update = true;
}

void sprite::Draw(ID3D11DeviceContext& rc)
{
	if (m_textureSRV == nullptr) {
		throw;
		return;
	}

	if (!f_update)
	{
		//アップデート関数が呼ばれてなければデフォルトでアップデート
		Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
		f_update = true;
	}


	SSpriteCB cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, m_view);
	cb.WVP.Mul(cb.WVP, m_proj);
	cb.mulColor = m_mulColor;

	rc.UpdateSubresource(m_cb.GetBody(),0,NULL,&cb,0,0);
	rc.VSSetConstantBuffers(0,1, &m_cb.GetBody());
	rc.PSSetConstantBuffers(0,1, &m_cb.GetBody());
	rc.VSSetShaderResources(0, 1, &m_textureSRV);
	rc.PSSetShaderResources(0, 1, &m_textureSRV);
	rc.PSSetShader((ID3D11PixelShader*)m_ps.GetBody(),NULL,0);
	rc.VSSetShader((ID3D11VertexShader*)m_vs.GetBody(),NULL,0);
	rc.IASetInputLayout(m_vs.GetInputLayout());
	rc.PSSetSamplers(0, 1, &m_samplerState);
	m_primitive.Draw(rc);
}

void sprite::PostEffectDraw(ID3D11DeviceContext& renderContext)
{
	if (m_textureSRV == nullptr) {
		throw;
		return;
	}
	renderContext.VSSetShaderResources(0, 1, &m_textureSRV);
	renderContext.PSSetShaderResources(0, 1, &m_textureSRV);
	renderContext.PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	renderContext.VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	renderContext.IASetInputLayout(m_vs.GetInputLayout());
	m_primitive.Draw(renderContext);
}