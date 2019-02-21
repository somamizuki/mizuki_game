#pragma once

#include"Class_of_NewGO.h"
#include"ObjectInfo.h"
#include"SpriteEffect.h"

using namespace BulletInfo;
class Player;
class bullet:public GameObject
{
public:
	bullet(int No, const char* obj_name);
	~bullet();

	bool Start();									//スタート関数(初期化とか)
	void Update();									//更新処理
	void Draw();									//描画
	void EffectDraw();

	/*ポジションをあげる関数*/
	const CVector3 Getpos() const
	{
		return bulletpos;
	}
	/*弾が発射されたかどうかを判定する*/
	bool isfire()
	{
		return fire;
	}

	void SetBulletParam()
	{
		if (!Get_isStart())
		{
			if (Start())
			{
				Set_isStart(true);
			}
		}
		switch (witchbullet)
		{
		case isPlayer: {
			speed = m_player->Get_PlayerMove().Length() + 500.0f;
			fire = true;
			break;
		}
		case isEnemy: {
			if (m_enemy != nullptr)
			{
				speed = m_enemy->Getmovespeed().Length() + bulletspeed;
				fire = true;
			}
			break;
		}
		default:
			break;
		}
	}

	void SetTarget(Enemy* enemy)
	{
		LockOnEnemy = enemy;
		if (LockOnEnemy != nullptr)
		{
			LockOnEnemy->AddDeleteGOListeners([&](GameObject* go)
			{
				LockOnEnemy = nullptr;
			});
		}
	}

	void SetLeft_or_Rite(LorR LR)
	{
		LeftRite = LR;
	}

	void SetEnemy(Enemy* enemy)
	{
		m_enemy = enemy;
		
	}

	void WitchBullet(witchBullet Witch)
	{
		witchbullet = Witch;
	}
	


	Enemy* Getm_enemy()
	{
		return m_enemy;
	}
	Player* Getm_player()
	{
		return m_player;
	}

private:
	void bulletFire();
	void UpdateVector();
	void BulletHoming(CVector3& target);
	float Acos(float dotresult)				//内積の結果が1.0～-1.0の範囲を超えないようにする。
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	//たま
	SkinModel m_tama;								//玉のモデル
	CVector3 tamadir = CVector3::Zero();			//玉のディレクション
	CVector3 bulletpos = CVector3::Zero();			//玉のポジション
	CQuaternion m_rotation = CQuaternion::Identity();//弾の回転
	float speed = 0.0f;								//玉の最終速度
	float m_time = 0.0f;
	Player* m_player = nullptr;						//プレイヤーのポインター
	CVector3 m_playerPos = CVector3::Zero();
	Enemy* LockOnEnemy = nullptr;					//ロックオンされたEnemyをさすポインター
	Enemy* m_enemy = nullptr;						//Enemyの弾のときEnemy自身をさすポインター
	Class_of_NewGO* CoN = nullptr;					//いろんなクラスをnewするクラスのポインター
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;//法線マップ用のSRV
	bool fire = false;								//ミサイル発射のフラグ
	bool PlayersBullet = false;						//trueならPlayerの弾
	bool EnemysBullet = false;						//trueならEnemyの弾
	bool isHoming = false;
	LorR LeftRite;									//enum,Leftなら左に、Riteなら右に弾をくっつける
	witchBullet witchbullet;						//enum,isPlayerならPlayerの、isEnemyならEnemyの弾
	/*モデルの軸、前、右、上*/
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_rite = CVector3::Zero();
	CVector3 m_up = CVector3::Zero();

	SpriteEffect m_spriteeffect;
	ShaderResourceView m_srv;
};

