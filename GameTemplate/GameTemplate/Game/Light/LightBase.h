#pragma once
using namespace Light;

class LightBase:Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LightBase();
	/// <summary>
	/// ストラクチャードバッファーのイニット
	/// </summary>
	/// <returns>bool</returns>
	virtual bool InitLightSB() { return true; }
	/// <summary>
	/// アップデート関数
	/// </summary>
	virtual void UpdateSubresource(){}
	/// <summary>
	/// ストラクチャードバッファーを送る
	/// </summary>
	virtual void SendStructuredBuffer(){}
	/// <summary>
	/// イニットされたかどうかのフラグをセット
	/// </summary>
	/// <param name="InitF">bool</param>
	void SetisInit(bool InitF)
	{
		isInit = InitF;
	}
	/// <summary>
	/// イニットされたかどうかのフラグをゲット
	/// </summary>
	/// <returns>bool</returns>
	bool GetisInit()
	{
		return isInit;
	}
	/// <summary>
	/// 構造体が初期化されたかどうかのフラグをセット
	/// </summary>
	/// <param name="initf">bool</param>
	void SetInitStruct(bool initf)
	{
		InitStruct = initf;
	}
	/// <summary>
	/// 構造体が初期化されたかどうかのフラグをゲット
	/// </summary>
	/// <returns>bool</returns>
	bool GetInitStruct()
	{
		return InitStruct;
	}
	/// <summary>
	/// ライトのタイプをセット
	/// </summary>
	/// <param name="lig">LightType</param>
	void SetLightType(LightType lig)
	{
		ligtype = lig;
	}
	/// <summary>
	/// ライトタイプのゲッター
	/// </summary>
	/// <returns>LightType</returns>
	const LightType& GetLightType()
	{
		return ligtype;
	}

private:
	bool		isInit = false;			//初期化フラグ
	bool		InitStruct = false;		//ストラクチャードバッファーの初期化フラグ
	LightType	ligtype = nolig;		//ライトタイプ
	


};


