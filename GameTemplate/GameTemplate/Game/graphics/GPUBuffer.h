#pragma once
class GPUBuffer:Noncopyable
{
public:
	GPUBuffer();
	virtual~GPUBuffer();

	bool Create(const void* pInitDate, D3D11_BUFFER_DESC& bufferDesc);

	ID3D11Buffer*&GetBody()
	{
		return m_gpuBuffer;
	}
	void Release();
private:
	ID3D11Buffer* m_gpuBuffer = nullptr;
};

