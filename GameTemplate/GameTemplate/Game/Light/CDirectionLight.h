#pragma once
class CDirectionLight:public LightBase
{
public:
	CDirectionLight();
	~CDirectionLight();
	bool InitLightSB();
	void UpdateSubresource();
	void SendStructuredBuffer();
	void SendConstantBuffer();

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
			throw;					//ディレクションライト置きすぎ！！
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
	StructuredBuffer m_sb;
	ConstantBuffer m_cb;
	static const int DirectionMaxSum = 8;
	int DirSum = 0;
	std::vector<SDirectionLight> s_Light;
	SDirectionLight ligstruct[DirectionMaxSum];
	bool creatf = false;
};

