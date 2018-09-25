#pragma once
class IndexBuffer
{
public:
	enum EnIndexType {
		enIndexType_16,
		enIndexType_32,
	};
	IndexBuffer();
	~IndexBuffer();

	bool Create(int numIndex, EnIndexType indexType, const void*pSrcIndexBuffer);

	void Release();

	EnIndexType GetIndexType() const
	{
		return m_indexType;
	}

	ID3D11Buffer* GetBody() const
	{
		return m_indexBuffer;
	}
	unsigned int GetNumIndex() const
	{
		return m_numIndex;
	}
private:
	ID3D11Buffer* m_indexBuffer = nullptr;
	EnIndexType m_indexType = enIndexType_16;
	unsigned int m_numIndex = 0;
};

