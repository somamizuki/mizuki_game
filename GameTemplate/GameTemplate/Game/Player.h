#pragma once
#include "ObjectInfo.h"
#include"character/HitObject.h"
#include"Enemy.h"
#include"SpriteEffect.h"
#include"level/Level.h"
#include "missileRechargeHUD.h"
#include"HPGaugeHUD.h"


class m_camera;
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
	void setposition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転のセッター
	/// </summary>
	/// <param name="rot">回転(CQuaternion)</param>
	void setrot(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ポジションのゲッター
	/// </summary>
	/// <returns>ポジション(CVector3)</returns>
	const CVector3& Getpos() const
	{
		return m_position;
	}
	/// <summary>
	/// 前方向のゲッター
	/// </summary>
	/// <returns>前方向(CVector3)</returns>
	const CVector3& Getforward() const
	{
		return m_forward;
	}
	/// <summary>
	/// 右方向のゲッター
	/// </summary>
	/// <returns>右方向(CVector3)</returns>
	const CVector3& Getrite() const
	{
		return m_rite;
	}
	/// <summary>
	/// 上方向のゲッター
	/// </summary>
	/// <returns>上方向(CVector3)</returns>
	const CVector3& Getup() const
	{
		return m_up;
	}
	/// <summary>
	/// プレイヤーの移動速度のゲッター
	/// </summary>
	/// <returns>移動速度(CVector3)</returns>
	const CVector3& Get_PlayerMove() const
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
		if (m_playerParam.Time <= 0.0f)
		{
			m_playerParam.HP = max(0, m_playerParam.HP - damage);
			m_playerParam.Time = nodamageeTime;
		}

	}

private:
	//プレイヤーのパラメーターを持った構造体
	struct playerParam
	{
		int HP = 100;
		float Time = 0.0f;
	};


	playerParam m_playerParam;							//プレイヤーのパラメーター
	const float HPMAX = m_playerParam.HP;				//HPの最大値
	const float nodamageeTime = 0.5f;					//無敵時間

	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//プレイヤーのポジション
	CQuaternion m_rotation = CQuaternion::Identity();	//プレイヤーの回転
	CVector3 movespeed = CVector3::Zero();				//移動速度
	CVector3 m_forward;									//前方向
	CVector3 m_rite;									//右方向
	CVector3 m_up;										//上方向
	ShaderResourceView aimSRV;							//エイムスプライトのシェーダーリソースビュー
	sprite aimsprite;									//エイムスプライト
	ShaderResourceView LockOnSRV;						//ロックオンスプライトのシェーダーリソースビュー
	sprite LockOnSprite;								//ロックオンスプライト
	CVector3 LockOnEnemyPos = { 0.0f,0.0f,0.0f };		//ロックオンされたスプライトのポジション


	float pad_X;									//パッドXの入力量
	float pad_Y;									//パッドYの入力量
	const float DefaultSpeed = 1800.0f;					//デフォルトの速度
	const float BoostSpeed = 3000.0f;					//ブースト時の速度
	const float RotSpeed_X = 3.0f;						//Z軸周りの回転スピード
	const float RotSpeed_Y = 2.0f;						//X軸周りの回転スピード
	const float RotSpeed_Tw = 0.3f;						//エイムを微調整する変数


	const float bulletspan = 1.0f;						//ミサイルの発射間隔
	float ritebulletTime = 0.0f;						//右ミサイルを発射してからの経過時間
	float leftbulletTime = 0.0f;						//左ミサイルを発射してからの経過時間
	float leftmissileGaugelevel = 1.0f;					//左ミサイルのゲージレベル
	float ritemissileGaugelevel = 1.0f;					//右ミサイルのゲージレベル

	bool LockOnflag = false;							//ロックオンフラグ

	float Speed = 0.0f;									//移動速度(サブ)

	void playermove();								//プレイヤーの移動関数
	void playerreturn();							//ミッションエリア外に出ないようにする
	void bossfightmove();							//ボス戦の移動
	void bossfightInit();							//ボス戦の初期化
	bool bossfightInitflag = false;					//ボス戦の初期化が完了かのフラグ
	BossEnemy* m_bossenemy = nullptr;				//ボスのポインター
	CVector3 m_bosspos = CVector3::Zero();			//ボスのポジション
	const float tobosslen = 9000.0f;				//ボスへの距離
	const float bosshight = 8000.0f;				//ボスの高さ
	CVector3 m_BosstoPlayer = CVector3::Zero();		//ボスからプレイヤーへのベクトル
	void vector();									//プレイヤーの前右上のベクトルを計算する関数
	void bulletManager();							//バレットを管理する関数
	Enemy* LockOnManager();							//ロックオンを管理する関数
	Enemy* prevLockOnEnemy = nullptr;				//前フレームでロックオンされていたエネミー
	void spritemanager();							//スプライトを管理する関数
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

	m_camera* camera = nullptr;						//カメラのポインター
	Class_of_NewGO* CofNG = nullptr;				//newするクラスのポインター
	bullet* RiteBullet = nullptr;					//右バレットのポインター
	bullet* LeftBullet = nullptr;					//左バレットのポインター
	enum PlayerState								//プレイヤーのステート
	{
		Nomal,		//通常
		Return,		//原点に戻る(ミッション範囲を超えた時)
		Boss,		//ボス戦
	};
	PlayerState pState = Nomal;
	HitObject m_characon;							//キャラコン

	/*ジェットエンジンの構造体*/
	struct Engin
	{
		SpriteEffect spriteeffect;
		CVector3 toEngin;
	};
	std::vector<Engin*> spriteeffect;			//ジェットエンジンのvector
	ShaderResourceView m_srv;					//ジェットエンジンのシェーダーリソースビュー
	Level playerenginlevel;						//エンジンのポジションが入ったレベル
	missileRechargeHUD m_leftRechargeHUD;		//左ミサイルのリチャージHUD
	missileRechargeHUD m_riteRechargeHUD;		//右ミサイルのリチャージHUD
	HPGaugeHUD m_hpHUD;							//HPのHUD

};

