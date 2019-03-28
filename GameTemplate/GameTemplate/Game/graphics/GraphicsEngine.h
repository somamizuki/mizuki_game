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
	/// <summary>
	/// �V���h�E�}�b�v�̃C���X�^���X���Z�b�g
	/// </summary>
	/// <param name="shadow">ShadowMap*</param>
	void SetShadowMap(ShadowMap* shadow)
	{
		m_shadowMap = shadow;
	}
	/// <summary>
	/// �V���h�E�}�b�v�̃Q�b�^�[
	/// </summary>
	/// <returns>ShadowMap*</returns>
	ShadowMap* GetShadowMap()
	{
		return m_shadowMap;
	}
	/// <summary>
	/// �u���[���̃Q�b�^�[
	/// </summary>
	/// <returns>Bloom*</returns>
	Bloom* GetBloom()
	{
		return &m_bloom;
	}
	/// <summary>
	/// SpriteBatch�̃Q�b�^�[
	/// </summary>
	/// <returns>DirectX::SpriteBatch*</returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spritefontBase;
	}
	/// <summary>
	/// SpriteFont�̃Q�b�^�[
	/// </summary>
	/// <returns>DirectX::SpriteFont*</returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_spritefont;
	}
	/// <summary>
	/// ���X�^���C�U�[�X�e�[�g�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
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
	ID3D11DepthStencilView* m_BackUpDSV = NULL;			//�o�b�N�A�b�v�f�v�X�X�e���V���r���[
	D3D11_VIEWPORT			m_mainViewport;				//���C���r���[�|�[�g
	D3D11_VIEWPORT			BackUpViewport;				//�o�b�N�A�b�v�r���[�|�[�g
	RenderTarget			m_mainRenderTarget;			//���C�������_�[�^�[�Q�b�g
	sprite					m_copyMainRtToFrameBufferSprite;//���C�������_�[�^�[�Q�b�g��`���X�v���C�g
	bool					RTspriteInitF = false;
	bool					backupF = false;
	ShadowMap*              m_shadowMap = nullptr;		//�V���h�E�}�b�v
	Bloom m_bloom;
	DirectX::SpriteBatch*	m_spritefontBase = nullptr;	//�X�v���C�g�o�b�`
	DirectX::SpriteFont*	m_spritefont = nullptr;		//�X�v���C�g�t�H���g
};

extern GraphicsEngine*		g_graphicsEngine;			//�O���t�B�b�N�X�G���W��