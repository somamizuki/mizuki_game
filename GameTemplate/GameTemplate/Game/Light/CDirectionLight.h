#pragma once
class CDirectionLight:public LightBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CDirectionLight();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CDirectionLight();
	/// <summary>
	/// ストラクチャードバッファーを初期化
	/// </summary>
	/// <returns>bool</returns>
	bool InitLightSB();
	/// <summary>
	/// サブリソースの更新
	/// </summary>
	void UpdateSubresource();
	/// <summary>
	/// ストラクチャードバッファーを送る
	/// </summary>
	void SendStructuredBuffer();
	/// <summary>
	/// 定数バッファを送る
	/// </summary>
	void SendConstantBuffer();
	/// <summary>
	/// ライトをセット
	/// </summary>
	/// <param name="dirlig">ディレクションライトの構造体(SDirectionLight)</param>
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
	StructuredBuffer m_sb;							//ストラクチャードバッファー
	ConstantBuffer m_cb;							//コンスタントバッファー
	static const int DirectionMaxSum = 8;			//ライトの最大数
	int DirSum = 0;									//ライトの数
	std::vector<SDirectionLight> s_Light;			//登録するライト
	SDirectionLight ligstruct[DirectionMaxSum];		//ライトの配列
};

