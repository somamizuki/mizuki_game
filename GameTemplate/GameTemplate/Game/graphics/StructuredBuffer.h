#pragma once
#include"ShaderResourceView.h"
#include"UnorderedAccessView.h"

class StructuredBuffer: Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StructuredBuffer();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StructuredBuffer();
	/// <summary>
	/// �N���G�[�g�֐�
	/// </summary>
	/// <param name="pInitData">�f�[�^</param>
	/// <param name="bufferDesc">�o�b�t�@�[�̐ݒ�(D3D11_BUFFER_DESC)</param>
	/// <returns>bool</returns>
	bool Create(const void*pInitData, D3D11_BUFFER_DESC& bufferDesc);
	/// <summary>
	/// �{�̂̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11Buffer</returns>
	ID3D11Buffer*& GetBody()
	{
		return m_structuredBuffer;
	}
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
	/// <summary>
	/// SRV�̃Q�b�^�[
	/// </summary>
	/// <returns>ShaderResourceView</returns>
	ShaderResourceView& GetSRV()
	{
		return m_srv;
	}
private:
	ID3D11Buffer*		m_structuredBuffer = nullptr;	//�o�b�t�@�[
	ShaderResourceView	m_srv;							//SRV
	UnorderedAccessView m_uav;							//UAV
};

