#pragma once
class CPointLight :public LightBase
{
public:
	CPointLight();
	~CPointLight();

	bool InitLightSB();
	void UpdateSubresource();
	void SendStructuredBuffer();
	void SendConstantBuffer();

	void SetLight(const SPointLight& pointlig)
	{
		int ligsum = 0;
		for (auto& lig_it : s_Light)
		{
			ligsum++;
		}
		if (ligsum < PointMaxSum)
		{
			s_Light.push_back(pointlig);
		}
		else
		{
			throw;					//�|�C���g���C�g�u�������I�I
		}
		ligsum = 0;
		for (auto& lig_it : s_Light)
		{
			ligstruct[ligsum] = lig_it;
			ligsum++;
		}
		this->SetInitStruct(true);
		PointSum = ligsum;
	}

private:
	StructuredBuffer m_sb;						//���C�g�̃X�g���N�`���[�h�o�b�t�@�[
	ConstantBuffer m_cb;						//���C�g�̃R���X�^���g�o�b�t�@�[
	static const int PointMaxSum = 1024;		//�|�C���g���C�g�̍ő吔
	int PointSum = 0.0f;						//�|�C���g���C�g�̐�
	std::vector<SPointLight> s_Light;
	SPointLight ligstruct[PointMaxSum];
	bool creatf = false;
};

