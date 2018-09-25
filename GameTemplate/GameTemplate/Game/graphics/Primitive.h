#pragma once
#include"VertexBuffer.h"
#include"IndexBuffer.h"
class Primitive
{
public:
	Primitive();
	~Primitive();
	bool Create(
		D3D_PRIMITIVE_TOPOLOGY topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		IndexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer
	);
	void Release();
	void Draw(ID3D11DeviceContext& rc);
private:
	VertexBuffer			m_vertexBuffer;		//!<���_�o�b�t�@�B
	IndexBuffer			m_indexBuffer;		//!<�C���f�b�N�X�o�b�t�@�B
	D3D_PRIMITIVE_TOPOLOGY	m_topology;			//!<�g�|���W�[�B
};

