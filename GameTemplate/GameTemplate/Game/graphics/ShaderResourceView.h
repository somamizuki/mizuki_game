#pragma once
class StructuredBuffer;
class TextureData;

class ShaderResourceView
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ShaderResourceView();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ShaderResourceView();
	/// <summary>
	/// �N���G�[�g�֐�
	/// </summary>
	/// <param name="structuredBuffer">�X�g���N�`���[�h�o�b�t�@�[</param>
	/// <returns></returns>
	bool Create(StructuredBuffer& structuredBuffer);
	/// <summary>
	/// �N���G�[�g�֐�
	/// </summary>
	/// <param name="texture">�e�N�X�`���[(ID3D11Texture2D)</param>
	/// <returns>bool</returns>
	bool Create(ID3D11Texture2D* texture);
	/// <summary>
	/// �t�@�C������dds���쐬����֐�
	/// </summary>
	/// <param name="fileName">�t�@�C���p�X(L"filepath")</param>
	/// <returns>bool</returns>
	bool CreateFromDDSTextureFromFile(const wchar_t* fileName);
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
	/// <summary>
	/// �{�̂̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11ShaderResourceView</returns>
	ID3D11ShaderResourceView*& GetBody()
	{
		return m_srv;
	}
	/// <summary>
	/// m_isValid�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	bool IsValid() const
	{
		return m_isValid;
	}
	/// <summary>
	/// �e�N�X�`���[�ݒ�
	/// </summary>
	/// <param name="desc">�ݒ�(D3D11_TEXTURE2D_DESC)</param>
	void GetTextureDesc(D3D11_TEXTURE2D_DESC& desc) const
	{
		ID3D11Texture2D* tex;
		m_srv->GetResource((ID3D11Resource**)&tex);
		tex->GetDesc(&desc);
		tex->Release();
	}
private:
	ID3D11ShaderResourceView*	m_srv = nullptr;	//SRV
	bool						m_isValid = false;	//�L�����ǂ����̃t���O
};