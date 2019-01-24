#include "stdafx.h"
#include "Bloom.h"


Bloom::Bloom()
{
}


Bloom::~Bloom()
{
}

void Bloom::Init()
{
	m_vs.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
	m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", Shader::EnType::PS);
	m_psFinal.Load("Assets/shader/bloom.fx", "PSFinal", Shader::EnType::PS);
	///////////////////////////////////////////////////////////////////////////
	//最適化のポイント②
	//ボケ画像合成用のピクセルシェーダーをロードする。
	m_psCombine.Load("Assets/shader/bloom.fx", "PSCombine", Shader::EnType::PS);

	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC dfblendDesc(defaultSettings);
	auto device = g_graphicsEngine->GetD3DDevice();

	dfblendDesc.RenderTarget[0].BlendEnable = true;
	dfblendDesc.RenderTarget[0].SrcBlend = dfblendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	dfblendDesc.RenderTarget[0].DestBlend = dfblendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	dfblendDesc.RenderTarget[0].BlendOp = dfblendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	device->CreateBlendState(&dfblendDesc, &m_disableBlendState);

	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	//最終合成用のブレンドステートを作成する。
	//最終合成は加算合成。
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&blendDesc, &m_finalBlendState);

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	
	m_luminanceRT.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_blurCombineRT.Create(
		FRAME_BUFFER_W / 2,
		FRAME_BUFFER_H / 2,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	ID3D11ShaderResourceView* SRV = m_luminanceRT.GetRenderTargetSRV();
	for (auto& gaussianBlur : m_gaussianblur) {
		gaussianBlur.Init(SRV);
		//次のガウスブラーで使用するソーステクスチャを設定する。
		SRV = gaussianBlur.GetResultTextureSRV();
	}

	m_sprite.Init(
		nullptr,
		2.0f,
		2.0f
	);
}

void Bloom::Update()
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	{
		//αブレンドを無効にする。
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

		//輝度抽出用のレンダリングターゲットに変更する。
		g_graphicsEngine->ChangeRenderTarget(&m_luminanceRT, m_luminanceRT.GetViewport());
		//レンダリングターゲットのクリア。
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_luminanceRT.ClearRenderTarget(clearColor);

		//シーンをテクスチャとする。
		ID3D11ShaderResourceView* mainRTTexSRV = g_graphicsEngine->GetmainRenderTarget()->GetRenderTargetSRV();
		m_sprite.SetTexture(mainRTTexSRV);
		m_sprite.SetScreen2DShader(&m_vs, &m_psLuminance);
		m_sprite.Draw(*deviceContext);
	}

	for (auto& gaussianBlur : m_gaussianblur) {
		gaussianBlur.Draw(&m_sprite, m_luminanceRT.GetRenderTargetSRV());
	}

	g_graphicsEngine->ChangeRenderTarget(&m_blurCombineRT, m_blurCombineRT.GetViewport());
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_blurCombineRT.ClearRenderTarget(clearColor);

	for (int registerNo = 0; registerNo < NumDownSampling; registerNo++) {
		auto srv = m_gaussianblur[registerNo].GetResultTextureSRV();
		deviceContext->PSSetShaderResources(registerNo, 1, &srv);
	}
	m_sprite.SetScreen2DShader(&m_vs, &m_psCombine);
	m_sprite.Draw(*deviceContext);
	{
		auto mainRT = g_graphicsEngine->GetmainRenderTarget();
		g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());
		deviceContext->ClearDepthStencilView(mainRT->GetDepthStensilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		//合成したボケテクスチャのアドレスをt0レジスタに設定する。
		auto srv = m_blurCombineRT.GetRenderTargetSRV();
		m_sprite.SetTexture(srv);

		//加算合成用のブレンディングステートを設定する。
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
		//フルスクリーン描画。
		m_sprite.SetScreen2DShader(&m_vs, &m_psFinal);
		m_sprite.Draw(*deviceContext);
		//ブレンディングステートを戻す。
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

	}
}