#pragma once
class IndexBuffer
{
public:
	/// <summary>
	/// �C���f�b�N�X�^�C�v
	/// </summary>
	enum EnIndexType {
		enIndexType_16,
		enIndexType_32,
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	IndexBuffer();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~IndexBuffer();
	/// <summary>
	/// �N���G�[�g�֐�
	/// </summary>
	/// <param name="numIndex">�C���f�b�N�X��</param>
	/// <param name="indexType">�C���f�b�N�X�^�C�v</param>
	/// <param name="pSrcIndexBuffer">�C���f�b�N�X�f�[�^</param>
	/// <returns>bool</returns>
	bool Create(int numIndex, EnIndexType indexType, const void*pSrcIndexBuffer);
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
	/// <summary>
	/// �C���f�b�N�X�^�C�v�̃Q�b�^�[
	/// </summary>
	/// <returns>EnIndexType</returns>
	EnIndexType GetIndexType() const
	{
		return m_indexType;
	}
	/// <summary>
	/// �{�̂̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11Buffer</returns>
	ID3D11Buffer* GetBody() const
	{
		return m_indexBuffer;
	}
	/// <summary>
	/// �C���f�b�N�X���̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	unsigned int GetNumIndex() const
	{
		return m_numIndex;
	}
private:
	ID3D11Buffer*	m_indexBuffer = nullptr;		//�C���f�b�N�X�o�b�t�@�[
	EnIndexType		m_indexType = enIndexType_16;	//�C���f�b�N�X�^�C�v
	unsigned int	m_numIndex = 0;					//�C���f�b�N�X��
};

