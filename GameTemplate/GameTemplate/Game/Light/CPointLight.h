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
	void Update(SPointLight* lig,char* name)
	{
		int ligsum = 0;
		for (const auto& lig_it : s_Light)
		{
			if (!(std::strcmp(name, lig_it.ligname))) break;
			ligsum++;
		}
		ligstruct[ligsum] = *lig;
	}

	void SetLight(const SPointLight& pointlig,char* name)
	{
		int ligsum = 0;
		for (auto& lig_it : s_Light)
		{
			ligsum++;
		}
		if (ligsum < PointMaxSum)
		{
			PointLightParam ligp;
			ligp.lig = pointlig;
			ligp.ligname = name;
			s_Light.push_back(ligp);
		}
		else
		{
			throw;					//ポイントライト置きすぎ！！
		}
		ligsum = 0;
		for (auto& lig_it : s_Light)
		{
			ligstruct[ligsum] = lig_it.lig;
			ligsum++;
		}
		this->SetInitStruct(true);
		PointSum = ligsum;
	}

private:
	struct PointLightParam
	{
		SPointLight lig;
		const char* ligname;
	};
	StructuredBuffer m_sb;						//ライトのストラクチャードバッファー
	ConstantBuffer m_cb;						//ライトのコンスタントバッファー
	static const int PointMaxSum = 1024;		//ポイントライトの最大数
	int PointSum = 0;						//ポイントライトの数

	std::vector<PointLightParam> s_Light;
	SPointLight ligstruct[PointMaxSum];

	bool creatf = false;
};

