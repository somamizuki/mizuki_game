#pragma once

class StructuredBuffer;
class UnorderedAccessView
{
public:
	UnorderedAccessView();
	~UnorderedAccessView();

	bool Create(StructuredBuffer& structuredBuffer);

	bool Create(ID3D11Texture2D* texture);

	void Release();

	ID3D11UnorderedAccessView*& GetBody()
	{
		return m_uav;
	}

	bool IsValid() const
	{
		return m_isValid;
	}
private:
	ID3D11UnorderedAccessView* m_uav = nullptr;
	bool m_isValid = false;
};

