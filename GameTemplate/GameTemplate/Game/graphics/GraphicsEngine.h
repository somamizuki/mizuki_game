#pragma once
#include"RenderTarget.h"
#include"ShadowMap.h"
#include"Bloom.h"
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	void ChangeRenderTarget(RenderTarget* RT, D3D11_VIEWPORT* VP);
	void ReSetRenderTarget();
	void RenderTargetDraw(RenderTarget* RT, ID3D11ShaderResourceView* SRV, D3D11_VIEWPORT* VP);
	RenderTarget* GetmainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	D3D11_VIEWPORT* GetmainViewport()
	{
		return &m_mainViewport;
	}
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}

	void SetShadowMap(ShadowMap* shadow)
	{
		m_shadowMap = shadow;
	}

	ShadowMap* GetShadowMap()
	{
		return m_shadowMap;
	}

	Bloom* GetBloom()
	{
		return &m_bloom;
	}
	
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RenderTargetView*           m_BackUpRT = NULL;
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	ID3D11DepthStencilView* m_BackUpDSV = NULL;
	D3D11_VIEWPORT			m_mainViewport;
	D3D11_VIEWPORT			BackUpViewport;
	RenderTarget m_mainRenderTarget;
	sprite m_copyMainRtToFrameBufferSprite;
	bool RTspriteInitF = false;
	bool backupF = false;
	ShadowMap*              m_shadowMap = nullptr;		//�V���h�E�}�b�v
	Bloom m_bloom;



};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��