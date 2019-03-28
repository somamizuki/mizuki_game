#pragma once
class Effect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Effect();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Effect();
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="filepath">L"filepath"</param>
	void Init(const wchar_t* filepath);
	/// <summary>
	/// エフェクト再生関数
	/// </summary>
	/// <param name="position">ポジション(CVector3)</param>
	/// <param name="scale">スケール(CVector3)</param>
	void Play(CVector3 position, CVector3 scale);
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// リリース関数
	/// </summary>
	void Release();
private:
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;				//エフェクトマネージャー
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;		//エフェクサーレンダー
	Effekseer::Effect* m_sampleEffect = nullptr;					//エフェクト
	Effekseer::Handle m_playEffectHandle = -1;						//エフェクトハンドル
};

