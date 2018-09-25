#pragma once
class StructuredBuffer;
class TextureData;

class ShaderResourceView
{
public:
	ShaderResourceView();
	~ShaderResourceView();
	bool Create(StructuredBuffer& structuredBuffer);
	bool Create(ID3D11Texture2D* texture);
	bool CreateFromDDSTextureFromFile(const wchar_t* fileName);
	void Release();
	ID3D11ShaderResourceView*& GetBody()
	{
		return m_srv;
	}
	bool IsValid() const
	{
		return m_isValid;
	}
	void GetTextureDesc(D3D11_TEXTURE2D_DESC& desc) const
	{
		ID3D11Texture2D* tex;
		m_srv->GetResource((ID3D11Resource**)&tex);
		tex->GetDesc(&desc);
		tex->Release();
	}
private:
	ID3D11ShaderResourceView* m_srv = nullptr;
	bool m_isValid = false;
};