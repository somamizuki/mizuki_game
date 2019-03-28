#pragma once
class RenderTarget
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RenderTarget();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RenderTarget();
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
	/// <summary>
	/// �N���G�C�g�֐�
	/// </summary>
	/// <param name="w">���𑜓x</param>
	/// <param name="h">�c�𑜓x</param>
	/// <param name="texFormat">�t�H�[�}�b�g</param>
	void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);
	/// <summary>
	/// �N���A�֐�
	/// </summary>
	/// <param name="clearColor">�J���[(float)</param>
	void ClearRenderTarget(float* clearColor);

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[�̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11RenderTargetView*</returns>
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}
	/// <summary>
	/// �f�v�X�X�e���V���r���[�̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11DepthStencilView*</returns>
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}
	/// <summary>
	/// �����_�����O�^�[�Q�b�g��SRV�̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11ShaderResourceView*</returns>
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}
	/// <summary>
	/// �r���[�|�[�g
	/// </summary>
	/// <returns>D3D11_VIEWPORT*</returns>
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
private:
	ID3D11Texture2D*			m_renderTargetTex = nullptr;		//!<�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<�����_�[�^�[�Q�b�g�r���[�B
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//!<�����_�����O�^�[�Q�b�g��SRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//!<�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<�f�v�X�X�e���V���r���[�B
	D3D11_VIEWPORT				m_viewport;							//!<�r���[�|�[�g�B
};

