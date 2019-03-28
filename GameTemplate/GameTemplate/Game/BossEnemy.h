#pragma once
#include "Player.h"
#include "CollisionDetection.h"
class BossEnemy :public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	BossEnemy(int No, const char* obj_name);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BossEnemy();
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
	/// ポジションのゲッター
	/// </summary>
	/// <returns>ポジション(CVector3)</returns>
	const CVector3& GetPos() const
	{
		return m_position;
	}
	/// <summary>
	/// 前方向のゲッター
	/// </summary>
	/// <returns>前方向(CVector3)</returns>
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/// <summary>
	/// 右方向のゲッター
	/// </summary>
	/// <returns>右方向(CVector3)</returns>
	const CVector3& GetRight() const
	{
		return m_right;
	}
	/// <summary>
	/// 上方向のゲッター
	/// </summary>
	/// <returns>上方向(CVector3)</returns>
	const CVector3& GetUp() const
	{
		return m_up;
	}
	/// <summary>
	/// ポジションのゲッター
	/// </summary>
	/// <param name="position">ポジションのセッター</param>
	void SetPos(CVector3 position)
	{
		m_position = position;
	}


private:
	void Vector();
	void rotmanager();
	/// <summary>
	/// 内積の結果が1.0～-1.0の範囲を超えないようにする関数
	/// </summary>
	/// <param name="dotresult">内積結果(float)</param>
	/// <returns></returns>
	float Acos(float dotresult)
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	Animation		m_animation;							//アニメーション
	AnimationClip	m_animationClip[1];						//アニメーションクリップ
	SkinModel		m_skinmodel;							//スキンモデル
	CVector3		m_position = CVector3::Zero();			//ポジション
	CQuaternion		m_rotation = CQuaternion::Identity();	//回転
	CVector3		m_scale = CVector3::One();				//スケール
	Player*			m_player = nullptr;						//プレイヤーのポインタ
	CVector3		m_right = CVector3::Right();			//右方向
	CVector3		m_up = CVector3::Up();					//上方向
	CVector3		m_forward = CVector3::Front();			//前方向
	CVector3		m_playerpos = CVector3::Zero();			//プレイヤーのポジション
	CVector3		m_oldbonepos = CVector3::Zero();		//前のボーンのポジション
	
};

