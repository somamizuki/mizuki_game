#pragma once
class VertexBuffer:Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	VertexBuffer();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~VertexBuffer();
	/// <summary>
	/// �N���G�[�g�֐�
	/// </summary>
	/// <param name="numVertex">���_��</param>
	/// <param name="stride">�o�C�g�̕�size</param>
	/// <param name="pSrcVertexBuffer">���_�o�b�t�@�[�f�[�^</param>
	/// <returns>bool</returns>
	bool Create(int numVertex, int stride, const void* pSrcVertexBuffer);
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
	/// <summary>
	/// �X�g���C�h�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	int GetStride() const
	{
		return m_stride;
	}
	/// <summary>
	/// �{�̂̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11Buffer</returns>
	ID3D11Buffer*& GetBody()
	{
		return m_vertexBuffer;
	}

private:
	ID3D11Buffer*	m_vertexBuffer = nullptr;		//���_�o�b�t�@�[
	int				m_stride = 0;					//�o�C�g�̕�
};

