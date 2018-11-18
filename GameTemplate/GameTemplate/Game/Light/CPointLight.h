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
			throw;					//ポイントライト置きすぎ！！
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
	StructuredBuffer m_sb;						//ライトのストラクチャードバッファー
	ConstantBuffer m_cb;						//ライトのコンスタントバッファー
	static const int PointMaxSum = 1024;		//ポイントライトの最大数
	int PointSum = 0.0f;						//ポイントライトの数
	std::vector<SPointLight> s_Light;
	SPointLight ligstruct[PointMaxSum];
	bool creatf = false;
};

