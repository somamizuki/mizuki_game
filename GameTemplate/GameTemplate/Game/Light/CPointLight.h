#pragma once
class CPointLight :public LightBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CPointLight();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CPointLight();
	/// <summary>
	/// �X�g���N�`���[�h�o�b�t�@�[�̏������֐�
	/// </summary>
	/// <returns>bool</returns>
	bool InitLightSB();
	/// <summary>
	/// �T�u���\�[�X�̍X�V
	/// </summary>
	void UpdateSubresource();
	/// <summary>
	/// �X�g���N�`���[�h�o�b�t�@�[�𑗂�֐�
	/// </summary>
	void SendStructuredBuffer();
	/// <summary>
	/// �萔�o�b�t�@�[�𑗂�֐�
	/// </summary>
	void SendConstantBuffer();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	/// <param name="lig">�|�C���g���C�g�̍\����(SPointLight*)</param>
	/// <param name="name">���O("name")</param>
	void Update(SPointLight* lig,char* name)
	{
		int ligsum = 0;
		for (const auto& lig_it : m_lightpushlist)
		{
			if (!(std::strcmp(name, lig_it.ligname))) break;
			ligsum++;
		}
		m_pointlight[ligsum] = *lig;
	}
	/// <summary>
	/// ���C�g���Z�b�g����֐�
	/// </summary>
	/// <param name="pointlig">�|�C���g���C�g�̍\����(SPointLight)</param>
	/// <param name="name">���O("name")</param>
	void SetLight(const SPointLight& pointlig,char* name)
	{
		int ligsum = 0;
		for (auto& lig_it : m_lightpushlist)
		{
			ligsum++;
		}
		if (ligsum < POINTLIGHTMAXSUM)
		{
			PointLightParam ligp;
			ligp.lig = pointlig;
			ligp.ligname = name;
			m_lightpushlist.push_back(ligp);
		}
		else
		{
			throw;					//�|�C���g���C�g�u�������I�I
		}
		ligsum = 0;
		for (auto& lig_it : m_lightpushlist)
		{
			m_pointlight[ligsum] = lig_it.lig;
			ligsum++;
		}
		this->SetInitStruct(true);
		m_pointlightsum = ligsum;
	}

private:
	/// <summary>
	/// �|�C���g���C�g�̍\����
	/// </summary>
	struct PointLightParam
	{
		SPointLight lig;
		const char* ligname;
	};
	StructuredBuffer m_sb;						//���C�g�̃X�g���N�`���[�h�o�b�t�@�[
	ConstantBuffer m_cb;						//���C�g�̃R���X�^���g�o�b�t�@�[
	static const int POINTLIGHTMAXSUM = 1024;		//�|�C���g���C�g�̍ő吔
	int m_pointlightsum = 0;							//�|�C���g���C�g�̐�

	std::vector<PointLightParam> m_lightpushlist;		//�|�C���g���C�g��o�^���郊�X�g
	SPointLight m_pointlight[POINTLIGHTMAXSUM];			//�|�C���g���C�g�̔z��
};

