#pragma once
#include"ShaderResourceView.h"
#include"UnorderedAccessView.h"

class StructuredBuffer: Noncopyable
{
public:
	StructuredBuffer();
	~StructuredBuffer();
	bool Create(const void*pInitData, D3D11_BUFFER_DESC& bufferDesc);
	ID3D11Buffer*& GetBody()
	{
		return m_structuredBuffer;
	}

	void Release();

	ShaderResourceView& GetSRV()
	{
		return m_srv;
	}
private:
	ID3D11Buffer* m_structuredBuffer = nullptr;
	ShaderResourceView m_srv;
	UnorderedAccessView m_uav;



};

