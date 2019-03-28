#pragma once
class CDirectionLight:public LightBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CDirectionLight();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CDirectionLight();
	/// <summary>
	/// �X�g���N�`���[�h�o�b�t�@�[��������
	/// </summary>
	/// <returns>bool</returns>
	bool InitLightSB();
	/// <summary>
	/// �T�u���\�[�X�̍X�V
	/// </summary>
	void UpdateSubresource();
	/// <summary>
	/// �X�g���N�`���[�h�o�b�t�@�[�𑗂�
	/// </summary>
	void SendStructuredBuffer();
	/// <summary>
	/// �萔�o�b�t�@�𑗂�
	/// </summary>
	void SendConstantBuffer();
	/// <summary>
	/// ���C�g���Z�b�g
	/// </summary>
	/// <param name="dirlig">�f�B���N�V�������C�g�̍\����(SDirectionLight)</param>
	void SetLight(const SDirectionLight& dirlig)
	{
		int ligsum = 0;
		for (auto& lig_it : s_Light)
		{
			ligsum++;
		}
		if (ligsum < DirectionMaxSum)
		{
			s_Light.push_back(dirlig);
		}
		else
		{
			throw;					//�f�B���N�V�������C�g�u�������I�I
		}
		ligsum = 0;
		for (auto& lig_it : s_Light)
		{
			ligstruct[ligsum] = lig_it;
			ligsum++;
		}
		this->SetInitStruct(true);
		DirSum = ligsum;
	}


private:
	StructuredBuffer m_sb;							//�X�g���N�`���[�h�o�b�t�@�[
	ConstantBuffer m_cb;							//�R���X�^���g�o�b�t�@�[
	static const int DirectionMaxSum = 8;			//���C�g�̍ő吔
	int DirSum = 0;									//���C�g�̐�
	std::vector<SDirectionLight> s_Light;			//�o�^���郉�C�g
	SDirectionLight ligstruct[DirectionMaxSum];		//���C�g�̔z��
};

