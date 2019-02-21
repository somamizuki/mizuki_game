#include "stdafx.h"
#include "GaussianBlur.h"


GaussianBlur::GaussianBlur()
{
}


GaussianBlur::~GaussianBlur()
{
}

void GaussianBlur::Init(ID3D11ShaderResourceView* SRV)
{
	m_SRV = SRV;
	ID3D11Texture2D* tex;
	m_SRV->GetResource((ID3D11Resource**)&tex);
	D3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);
	tex->Release();
	resoluteW = texDesc.Width;
	resoluteH = texDesc.Height;
	m_downsampleRT[enRenderTarget_XBlur].Create(
		resoluteW/2.0f,
		resoluteH,
		texDesc.Format
	);
	m_downsampleRT[enRenderTarget_YBlur].Create(
		resoluteW / 2.0f,
		resoluteH / 2.0f,
		texDesc.Format
	);
	m_vsXBlur.Load("Assets/shader/GaussianBlur.fx", "VSXBlur", Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/GaussianBlur.fx", "VSYBlur", Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/GaussianBlur.fx", "PSBlur", Shader::EnType::PS);

	m_blurCbGpu.Create(nullptr, sizeof(SBlurParam));

}

void GaussianBlur::UpdateWeights()
{
	//�K�E�X�t�B���^�̏d�݂��X�V����B
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurIntensity);
		total += 2.0f*m_blurParam.weights[i];
	}
	// �K�i���B�d�݂̃g�[�^����1.0�ɂȂ�悤�ɁA�S�̂̏d�݂ŏ��Z���Ă���B
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}

void GaussianBlur::Draw(sprite* postEffectSprite, ID3D11ShaderResourceView* srv)
{

	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//�K�E�V�A���t�B���^�[�̏d�݃e�[�u�����X�V����B
	UpdateWeights();

	//�d�݃e�[�u�����X�V�����̂ŁAVRAM��̒萔�o�b�t�@���X�V����B
	//���C���������̓��e��VRAM�ɃR�s�[�B
	auto d3d11CbGpu = m_blurCbGpu.GetBody();
	deviceContext->UpdateSubresource(
		d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
	//���W�X�^b0��m_blurCbGpu�̃A�h���X��ݒ肷��B
	deviceContext->PSSetConstantBuffers(
		0, 1, &d3d11CbGpu);


	g_graphicsEngine->ChangeRenderTarget(
		&m_downsampleRT[enRenderTarget_XBlur],
		m_downsampleRT[enRenderTarget_XBlur].GetViewport()
	);
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_downsampleRT[enRenderTarget_XBlur].ClearRenderTarget(clearColor);
	postEffectSprite->SetTexture(m_SRV);
	postEffectSprite->SetShader(&m_vsXBlur, &m_psBlur);
	postEffectSprite->PostEffectDraw(*deviceContext);

	g_graphicsEngine->ChangeRenderTarget(
		&m_downsampleRT[enRenderTarget_YBlur],
		m_downsampleRT[enRenderTarget_YBlur].GetViewport()
	);

	m_downsampleRT[enRenderTarget_YBlur].ClearRenderTarget(clearColor);
	postEffectSprite->SetTexture(m_downsampleRT[enRenderTarget_XBlur].GetRenderTargetSRV());
	postEffectSprite->SetShader(&m_vsYBlur, &m_psBlur);
	postEffectSprite->PostEffectDraw(*deviceContext);


}