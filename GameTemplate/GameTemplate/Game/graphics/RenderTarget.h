#pragma once
class RenderTarget
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RenderTarget();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~RenderTarget();
	/// <summary>
	/// リリース関数
	/// </summary>
	void Release();
	/// <summary>
	/// クリエイト関数
	/// </summary>
	/// <param name="w">横解像度</param>
	/// <param name="h">縦解像度</param>
	/// <param name="texFormat">フォーマット</param>
	void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);
	/// <summary>
	/// クリア関数
	/// </summary>
	/// <param name="clearColor">カラー(float)</param>
	void ClearRenderTarget(float* clearColor);

	/// <summary>
	/// レンダーターゲットビューのゲッター
	/// </summary>
	/// <returns>ID3D11RenderTargetView*</returns>
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}
	/// <summary>
	/// デプスステンシルビューのゲッター
	/// </summary>
	/// <returns>ID3D11DepthStencilView*</returns>
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}
	/// <summary>
	/// レンダリングターゲットのSRVのゲッター
	/// </summary>
	/// <returns>ID3D11ShaderResourceView*</returns>
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}
	/// <summary>
	/// ビューポート
	/// </summary>
	/// <returns>D3D11_VIEWPORT*</returns>
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
private:
	ID3D11Texture2D*			m_renderTargetTex = nullptr;		//!<レンダリングターゲットとなるテクスチャ。
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<レンダーターゲットビュー。
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//!<レンダリングターゲットのSRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//!<デプスステンシルとなるテクスチャ。
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<デプスステンシルビュー。
	D3D11_VIEWPORT				m_viewport;							//!<ビューポート。
};

