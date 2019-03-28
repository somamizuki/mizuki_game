#pragma once
class missileRechargeHUD
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	missileRechargeHUD();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~missileRechargeHUD();
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="waku_filepath">枠L"filepath"</param>
	/// <param name="filepath">メーターL"filepath"</param>
	/// <param name="W">幅</param>
	/// <param name="H">高さ</param>
	void Init(const wchar_t* waku_filepath, const wchar_t* filepath, float W, float H);
	/// <summary>
	/// アップデート関数
	/// </summary>
	/// <param name="position">ポジション(CVector3)</param>
	/// <param name="m_rotation">ローテーション(CQuaternion)</param>
	/// <param name="Gaugelevel">ゲージレベル(float)</param>
	void Update(CVector3 position, CQuaternion m_rotation, float Gaugelevel);
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
private:
	ShaderResourceView	m_SRV;				//メーターのSRV
	ShaderResourceView	m_waku_SRV;			//枠のSRV
	sprite				m_waku_sprite;		//枠のスプライト
	sprite				m_sprite;			//メーターのスプライト
};

