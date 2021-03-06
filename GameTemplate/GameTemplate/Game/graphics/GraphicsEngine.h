#pragma once
#include"RenderTarget.h"
#include"ShadowMap.h"
#include"Bloom.h"
/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
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
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// シャドウマップのインスタンスをセット
	/// </summary>
	/// <param name="shadow">ShadowMap*</param>
	void SetShadowMap(ShadowMap* shadow)
	{
		m_shadowMap = shadow;
	}
	/// <summary>
	/// シャドウマップのゲッター
	/// </summary>
	/// <returns>ShadowMap*</returns>
	ShadowMap* GetShadowMap()
	{
		return m_shadowMap;
	}
	/// <summary>
	/// ブルームのゲッター
	/// </summary>
	/// <returns>Bloom*</returns>
	Bloom* GetBloom()
	{
		return &m_bloom;
	}
	/// <summary>
	/// SpriteBatchのゲッター
	/// </summary>
	/// <returns>DirectX::SpriteBatch*</returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spritefontBase;
	}
	/// <summary>
	/// SpriteFontのゲッター
	/// </summary>
	/// <returns>DirectX::SpriteFont*</returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_spritefont;
	}
	/// <summary>
	/// ラスタライザーステートのゲッター
	/// </summary>
	/// <returns></returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RenderTargetView*           m_BackUpRT = NULL;
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	ID3D11DepthStencilView* m_BackUpDSV = NULL;			//バックアップデプスステンシルビュー
	D3D11_VIEWPORT			m_mainViewport;				//メインビューポート
	D3D11_VIEWPORT			BackUpViewport;				//バックアップビューポート
	RenderTarget			m_mainRenderTarget;			//メインレンダーターゲット
	sprite					m_copyMainRtToFrameBufferSprite;//メインレンダーターゲットを描くスプライト
	bool					RTspriteInitF = false;
	bool					backupF = false;
	ShadowMap*              m_shadowMap = nullptr;		//シャドウマップ
	Bloom m_bloom;
	DirectX::SpriteBatch*	m_spritefontBase = nullptr;	//スプライトバッチ
	DirectX::SpriteFont*	m_spritefont = nullptr;		//スプライトフォント
};

extern GraphicsEngine*		g_graphicsEngine;			//グラフィックスエンジン