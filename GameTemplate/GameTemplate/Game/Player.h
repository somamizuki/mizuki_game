#pragma once
#include "ObjectInfo.h"
#include"character/HitObject.h"
#include"Enemy.h"
#include"SpriteEffect.h"
#include"level/Level.h"
#include "missileRechargeHUD.h"
#include"HPGaugeHUD.h"


class GameCamera;
class bullet;
class Class_of_NewGO;
class BossEnemy;
using namespace PlayerInfo;
class Player :public GameObject
{
public:
	Player(int No, const char* obj_name);
	~Player();
	/// <summary>
	/// スタート関数
	/// </summary>
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
	/// エフェクト描画
	/// </summary>
	void EffectDraw();
	/// <summary>
	/// 手前に描画したいものの描画
	/// </summary>
	void PostDraw();
	/// <summary>
	/// UI描画
	/// </summary>
	void UIDraw();
	/// <summary>
	/// DeleteGO時に呼ばれる関数
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// ポジションのセッター
	/// </summary>
	/// <param name="pos">ポジション(CVector3)</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転のセッター
	/// </summary>
	/// <param name="rot">回転(CQuaternion)</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ポジションのゲッター
	/// </summary>
	/// <returns>ポジション(CVector3)</returns>
	const CVector3& GetPosition() const
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
	const CVector3& GetRite() const
	{
		return m_rite;
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
	/// プレイヤーの移動速度のゲッター
	/// </summary>
	/// <returns>移動速度(CVector3)</returns>
	const CVector3& GetMoveSpeed() const
	{
		return movespeed;
	}

	/// <summary>
	/// 回転のゲッター
	/// </summary>
	/// <returns>回転(CQuaternion)</returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// HPのセッター
	/// </summary>
	/// <param name="damage">ダメージ量(int)</param>
	void SetHP(int damage)
	{
		if (m_playerparam.Time <= 0.0f)
		{
			m_playerparam.HP = max(0, m_playerparam.HP - damage);
			m_playerparam.Time = NODAMAGETIME;
		}

	}

private:
	//プレイヤーのパラメーターを持った構造体
	struct PlayerParam
	{
		int		HP = 50;
		float	Time = 0.0f;
	};


	PlayerParam					m_playerparam;							//プレイヤーのパラメーター
	const float					HPMAX = m_playerparam.HP;				//HPの最大値
	const float					NODAMAGETIME = 0.5f;					//無敵時間

	SkinModel					m_skinmodel;								//スキンモデル。
	CVector3					m_position = CVector3::Zero();			//プレイヤーのポジション
	CQuaternion					m_rotation = CQuaternion::Identity();	//プレイヤーの回転
	CVector3					movespeed = CVector3::Zero();			//移動速度
	CVector3					m_forward;								//前方向
	CVector3					m_rite;									//右方向
	CVector3					m_up;									//上方向
	ShaderResourceView			m_aimSRV;								//エイムスプライトのシェーダーリソースビュー
	sprite						m_aimsprite;							//エイムスプライト
	ShaderResourceView			m_lockonSRV;							//ロックオンスプライトのシェーダーリソースビュー
	sprite						m_lockonsprite;							//ロックオンスプライト
	CVector3					m_lockonenemypos = { 0.0f,0.0f,0.0f };	//ロックオンされたスプライトのポジション


	float						pad_X;									//パッドXの入力量
	float						pad_Y;									//パッドYの入力量
	const float					DEFAULTSPEED = 1800.0f;					//デフォルトの速度
	const float					BOOSTSPEED = 3000.0f;					//ブースト時の速度
	const float					ROTSPEED_X = 3.0f;						//Z軸周りの回転スピード
	const float					ROTSPEED_Y = 2.0f;						//X軸周りの回転スピード
	const float					ROTSPEED_TW = 0.3f;						//エイムを微調整する変数


	const float					BULLETSPAN = 1.0f;						//ミサイルの発射間隔
	float						m_ritebullettime = 0.0f;				//右ミサイルを発射してからの経過時間
	float						m_leftbullettime = 0.0f;				//左ミサイルを発射してからの経過時間
	float						m_leftmissilegaugelevel = 1.0f;			//左ミサイルのゲージレベル
	float						m_ritemissilegaugelevel = 1.0f;			//右ミサイルのゲージレベル

	bool						m_lockonflag = false;					//ロックオンフラグ

	float						m_nowspeed = 0.0f;						//移動速度(サブ)

	void PlayerMove();				//プレイヤーの移動関数
	void PlayerReturn();			//ミッションエリア外に出ないようにする
	void BossFightMove();			//ボス戦の移動
	void BossFightInit();			//ボス戦の初期化
	bool						m_bossfightinitflag = false;			//ボス戦の初期化が完了かのフラグ
	BossEnemy*					m_bossenemy = nullptr;					//ボスのポインター
	CVector3					m_bossposition = CVector3::Zero();		//ボスのポジション
	const float					TOBOSSLENGTH = 9000.0f;					//ボスへの距離
	const float					BOSSHEIGHT = 8000.0f;					//ボスの高さ
	CVector3					m_bosstoplayer = CVector3::Zero();		//ボスからプレイヤーへのベクトル
	void Vector();														//プレイヤーの前右上のベクトルを計算する関数
	void BulletManager();												//バレットを管理する関数
	Enemy* LockOnManager();												//ロックオンを管理する関数
	Enemy*						m_prevlockonenemy = nullptr;			//前フレームでロックオンされていたエネミー
	void SpriteManager();												//スプライトを管理する関数
	/// <summary>
	/// 内積の結果が1.0～-1.0の範囲を超えないようにする。
	/// </summary>
	/// <param name="dotresult">内積結果(float)</param>
	/// <returns>角度ラジアン(float)</returns>
	float Acos(float dotresult)
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	GameCamera*					m_camera = nullptr;				//カメラのポインター
	Class_of_NewGO*				m_class_of_newgo = nullptr;		//newするクラスのポインター
	bullet*						m_ritebullet = nullptr;			//右バレットのポインター
	bullet*						m_leftbullet = nullptr;			//左バレットのポインター
	enum PlayerState		//プレイヤーのステート
	{
		Nomal,		//通常
		Return,		//原点に戻る(ミッション範囲を超えた時)
		Boss,		//ボス戦
	};
	PlayerState					m_playerstate = Nomal;
	HitObject					m_characon;						//キャラコン

	/*ジェットエンジンの構造体*/
	struct Engin
	{
		SpriteEffect	m_spriteeffect;
		CVector3		m_toengin;
	};
	std::vector<Engin*>			m_spriteeffectlist;				//ジェットエンジンのvector
	ShaderResourceView			m_effectSRV;					//ジェットエンジンのシェーダーリソースビュー
	Level						m_playerenginlevel;				//エンジンのポジションが入ったレベル
	missileRechargeHUD			m_leftrechargeHUD;				//左ミサイルのリチャージHUD
	missileRechargeHUD			m_riterechargeHUD;				//右ミサイルのリチャージHUD
	HPGaugeHUD					m_hpHUD;						//HPのHUD

};

