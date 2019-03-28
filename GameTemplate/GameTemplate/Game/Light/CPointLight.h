#pragma once
class CPointLight :public LightBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CPointLight();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CPointLight();
	/// <summary>
	/// ストラクチャードバッファーの初期化関数
	/// </summary>
	/// <returns>bool</returns>
	bool InitLightSB();
	/// <summary>
	/// サブリソースの更新
	/// </summary>
	void UpdateSubresource();
	/// <summary>
	/// ストラクチャードバッファーを送る関数
	/// </summary>
	void SendStructuredBuffer();
	/// <summary>
	/// 定数バッファーを送る関数
	/// </summary>
	void SendConstantBuffer();
	/// <summary>
	/// アップデート関数
	/// </summary>
	/// <param name="lig">ポイントライトの構造体(SPointLight*)</param>
	/// <param name="name">名前("name")</param>
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
	/// ライトをセットする関数
	/// </summary>
	/// <param name="pointlig">ポイントライトの構造体(SPointLight)</param>
	/// <param name="name">名前("name")</param>
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
			throw;					//ポイントライト置きすぎ！！
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
	/// ポイントライトの構造体
	/// </summary>
	struct PointLightParam
	{
		SPointLight lig;
		const char* ligname;
	};
	StructuredBuffer m_sb;						//ライトのストラクチャードバッファー
	ConstantBuffer m_cb;						//ライトのコンスタントバッファー
	static const int POINTLIGHTMAXSUM = 1024;		//ポイントライトの最大数
	int m_pointlightsum = 0;							//ポイントライトの数

	std::vector<PointLightParam> m_lightpushlist;		//ポイントライトを登録するリスト
	SPointLight m_pointlight[POINTLIGHTMAXSUM];			//ポイントライトの配列
};

