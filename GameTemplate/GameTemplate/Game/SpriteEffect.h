#pragma once
class SpriteEffect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpriteEffect();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	~SpriteEffect();
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="SRV">SRV(ID3D11ShaderResourceView*)</param>
	/// <param name="time">消える時間(float)</param>
	/// <param name="span">発生頻度フレーム(int)</param>
	void Init(ID3D11ShaderResourceView* SRV, float time, int span);
	/// <summary>
	/// アップデート関数
	/// </summary>
	/// <param name="position">発生させるポジション</param>
	void Update(CVector3& position);
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
private:
	/// <summary>
	/// スプライトを発生させる関数
	/// </summary>
	/// <param name="position">CVector3</param>
	void GenerateSprite(CVector3 position);
	/// <summary>
	/// 内積の結果が1.0～-1.0の範囲を超えないようにする。
	/// </summary>
	/// <param name="dotresult">内積結果(float)</param>
	/// <returns>角度ラジアン(float)</returns>
	float Acos(float dotresult)
	{
		float angle = acosf(min(1.0f, max(-1.0f, dotresult)));
		return angle;
	}

private:
	/// <summary>
	/// EffectSpriteの構造体
	/// </summary>
	struct SEffectSprite{
		sprite m_sprite;
		CVector3 m_position = CVector3::Zero();
		CVector3 m_forward = CVector3::AxisZ()*-1.0f;
		CVector3 m_rite = CVector3::AxisX()*-1.0f;
		CVector3 m_up = CVector3::AxisY();
		float size = 0.2f;
		float time = 0.0f;
		bool dethflag = false;
		bool Initflag = false;
	};

	std::list<SEffectSprite*> EffectSpriteList;		//SEffectSpriteの配列
	ID3D11ShaderResourceView* m_SRV;				//スプライトのSRV
	float m_time = 0.0f;							//経過時間
	float changesize = 0.0f;						//スプライトの拡大縮小
	float eraseTime;								//消える時間
	int m_frame = 0;								//経過フレーム
	int m_Span;										//発生頻度フレーム
};

