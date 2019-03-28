#pragma once
#include"SkinModelEffect.h"
#include "SkinModelDataManager.h"
class sky:public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	sky(int No, const char* obj_name);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~sky();
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="mapfilepath">テクスチャーファイルパス(L"filepath")</param>
	/// <param name="modelfilePath">モデルファイルパス(L"filepath")</param>
	/// <param name="scale">スケール(CVector3)</param>
	void Init(const wchar_t* mapfilepath, const wchar_t* modelfilePath, CVector3 scale);
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns>bool</returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// スケールを再設定する関数
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ポジションをセットする関数
	/// </summary>
	/// <param name="pos">ポジション(CVector3)</param>
	void SetPositon(CVector3& pos)
	{
		m_position = pos;
	}

private:
	SkinModel			m_skinmodel;					//スキンモデル
	ShaderResourceView	m_skycube;						//キューブマップのSRV
	CVector3			m_scale;						//スケール
	CVector3			m_position = CVector3::Zero();	//ポジション
};

