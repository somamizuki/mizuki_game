#pragma once

class StructuredBuffer;
class UnorderedAccessView
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UnorderedAccessView();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UnorderedAccessView();
	/// <summary>
	/// �N���G�C�g�֐�
	/// </summary>
	/// <param name="structuredBuffer">�X�g���N�`���[�h�o�b�t�@�[(StructuredBuffer)</param>
	/// <returns>bool</returns>
	bool Create(StructuredBuffer& structuredBuffer);
	/// <summary>
	/// �N���G�C�g�֐�
	/// </summary>
	/// <param name="texture">ID3D11Texture2D&</param>
	/// <returns>bool</returns>
	bool Create(ID3D11Texture2D* texture);
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
	/// <summary>
	/// �{�̂̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11UnorderedAccessView</returns>
	ID3D11UnorderedAccessView*& GetBody()
	{
		return m_uav;
	}
	/// <summary>
	/// IsValid�̃Q�b�^�[
	/// </summary>
	/// <returns>bool</returns>
	bool IsValid() const
	{
		return m_isValid;
	}
private:
	ID3D11UnorderedAccessView*	m_uav = nullptr;	//UAV
	bool						m_isValid = false;	//�L�����ǂ����̃t���O
};

