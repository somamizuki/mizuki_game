#pragma once

#include"Class_of_NewGO.h"
#include"ObjectInfo.h"
#include"SpriteEffect.h"

using namespace BulletInfo;
class Player;
class bullet :public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	bullet(int No, const char* obj_name);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~bullet();
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// アップデート
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// エフェクト描画
	/// </summary>
	void EffectDraw();
	/// <summary>
	/// Delete時に呼ばれる関数
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// ポジションのゲッター
	/// </summary>
	/// <returns>CVector3</returns>
	const CVector3 Getpos() const
	{
		return m_position;
	}
	/// <summary>
	/// 発射されたか
	/// </summary>
	/// <returns>bool</returns>
	bool isfire()
	{
		return m_fireflag;
	}
	/// <summary>
	/// バレットのパラメーターをセット
	/// </summary>
	void SetBulletParam()
	{
		if (!Get_isStart())
		{
			if (Start())
			{
				Set_isStart(true);
			}
		}
		switch (m_witchbullet)
		{
		case isPlayer: {
			m_speed = m_player->GetMoveSpeed().Length() + 500.0f;
			m_fireflag = true;
			break;
		}
		case isEnemy: {
			if (m_enemy != nullptr)
			{
				m_speed = m_enemy->GetMoveSpeed().Length() + bulletspeed;
				m_fireflag = true;
			}
			break;
		}
		default:
			break;
		}
	}
	/// <summary>
	/// ロックオンしたエネミーをセット
	/// </summary>
	/// <param name="enemy"></param>
	void SetTarget(Enemy* enemy)
	{
		m_lockonenemy = enemy;
		if (m_lockonenemy != nullptr)
		{
			m_lockonenemy->RemoveHasMyPointerObject(this);
			m_lockonenemy->AddMyPointer<Enemy, bullet>(&m_lockonenemy, this);
		}
	}
	/// <summary>
	/// 左右どちらかを選択
	/// </summary>
	/// <param name="LR">LorR</param>
	void SetLeft_or_Rite(LorR LR)
	{
		m_left_or_rite = LR;
	}
	/// <summary>
	/// エネミーの弾の場合、自身をセット
	/// </summary>
	/// <param name="enemy"></param>
	void SetEnemy(Enemy* enemy)
	{
		m_enemy = enemy;
	}
	/// <summary>
	/// PlayerとEnemyどちらのバレットかをセット
	/// </summary>
	/// <param name="Witch">witchBullet</param>
	void WitchBullet(witchBullet Witch)
	{
		m_witchbullet = Witch;
	}
	/// <summary>
	/// エネミーのゲッター
	/// </summary>
	/// <returns>Enemy*</returns>
	Enemy* Getm_enemy()
	{
		return m_enemy;
	}
	/// <summary>
	/// プレイヤーのゲッター
	/// </summary>
	/// <returns>Player*</returns>
	Player* Getm_player()
	{
		return m_player;
	}
private:
	void BulletFire();
	void UpdateVector();
	void BulletHoming(CVector3& target);
	float Acos(float dotresult)				//内積の結果が1.0～-1.0の範囲を超えないようにする。
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	//たま
	SkinModel			m_skinmodel;							//ミサイルのモデル
	CVector3			m_movedirection = CVector3::Zero();		//ミサイルのディレクション
	CVector3			m_position = CVector3::Zero();			//ミサイルのポジション
	CQuaternion			m_rotation = CQuaternion::Identity();	//ミサイルの回転
	float				m_speed = 0.0f;							//ミサイルの最終速度
	float				m_time = 0.0f;							//ミサイルの最大飛行時間
	Player*				m_player = nullptr;						//プレイヤーのポインター
	CVector3			m_playerposition = CVector3::Zero();	//プレイヤーのポジション
	Enemy*				m_lockonenemy = nullptr;				//ロックオンされたEnemyをさすポインター
	Enemy*				m_enemy = nullptr;						//Enemyの弾のときEnemy自身をさすポインター
	Class_of_NewGO*		m_class_of_newgo = nullptr;				//いろんなクラスをnewするクラスのポインター
	bool				m_fireflag = false;						//ミサイル発射のフラグ
	bool				m_isplayersbullet = false;				//trueならPlayerの弾
	bool				m_isenemysbullet = false;				//trueならEnemyの弾
	bool				m_ishoming = false;						//追跡フラグ
	LorR				m_left_or_rite;							//enum,Leftなら左に、Riteなら右に弾をくっつける
	witchBullet			m_witchbullet;							//enum,isPlayerならPlayerの、isEnemyならEnemyの弾
	/*モデルの軸、前、右、上*/
	CVector3			m_forward = CVector3::Zero();
	CVector3			m_rite = CVector3::Zero();
	CVector3			m_up = CVector3::Zero();

	SpriteEffect		m_spriteeffect;							//スプライトエフェクト(パーティクルのような実装)
	ShaderResourceView	m_srv;									//エフェクトのSRV
};

