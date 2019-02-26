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
using namespace PlayerInfo;
class Player:public GameObject
{
public:
	Player(int No, const char* obj_name);
	~Player();
	bool Start();								//スタート関数
	void Update();								//アップデート関数
	void Draw();								//描画関数
	void EffectDraw();
	void PostDraw();							//手前に描画したいものの描画
	void UIDraw();
	void OnDestroy();
	void setposition(CVector3 pos)				//ポジションのセッター
	{
		m_position = pos;
	}
	void setrot(CQuaternion rot)				//回転のセッター
	{
		m_rotation = rot;
	}
	const CVector3& Getpos() const				//ポジションのゲッター
	{
		return m_position;
	}

	const CVector3& Getforward() const			//前方向のゲッター
	{
		return m_forward;
	}

	const CVector3& Getrite() const				//右方向のゲッター
	{
		return m_rite;
	}

	const CVector3& Getup() const				//上方向のゲッター
	{
		return m_up;
	}

	const CVector3& Get_PlayerMove() const		//プレイヤーの移動速度のゲッター
	{
		return movespeed;
	}


	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	void SetHP(int damage)
	{
		m_playerParam.HP -= damage;
	}
	
private:
	//プレイヤーのパラメーター
	struct playerParam
	{
		int HP = 50;
	};


	playerParam m_playerParam;
	const float HPMAX = m_playerParam.HP;

	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//プレイヤーのポジション
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 movespeed = CVector3::Zero();				//movespeed
	CMatrix rot_M;
	CVector3 m_forward;
	CVector3 m_rite;
	CVector3 m_up;
	ShaderResourceView aimSRV;
	sprite aimsprite;
	ShaderResourceView LockOnSRV;
	sprite LockOnSprite;
	CVector3 LockOnEnemyPos = { 0.0f,0.0f,0.0f };


	float pad_X;									//パッドXの入力量
	float pad_Y;									//パッドYの入力量
	const float DefaultSpeed = 2000.0f;					//デフォルトの速度
	const float BoostSpeed = 4000.0f;					//ブースト時の速度
	const float RotSpeed_X = 3.0f;						//Z軸周りの回転スピード
	const float RotSpeed_Y = 2.0f;						//X軸周りの回転スピード
	const float RotSpeed_Tw = 0.3f;						//エイムを微調整する変数

	
	const float bulletspan = 3.0f;
	float ritebulletTime = 0.0f;
	float leftbulletTime = 0.0f;
	float leftmissileGaugelevel = 1.0f;
	float ritemissileGaugelevel = 1.0f;

	bool LockOnflag = false;

	float Speed = 0.0f;

	void playermove();								//プレイヤーの移動関数
	void playerreturn();							//ミッションエリア外に出ないようにする
	void vector();									//プレイヤーの前右上のベクトルを計算する関数
	void bulletManager();
	Enemy* LockOnManager();
	Enemy* prevLockOnEnemy = nullptr;
	void spritemanager();
	float Acos(float dotresult)				//内積の結果が1.0～-1.0の範囲を超えないようにする。
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	m_camera* camera = nullptr;						//カメラのポインター
	Class_of_NewGO* CofNG = nullptr;
	bullet* RiteBullet = nullptr;
	bullet* LeftBullet = nullptr;
	std::vector<Enemy*> Enemys;
	enum PlayerState								//プレイヤーのステート
	{
		Nomal,		//通常
		Return		//原点に戻る(ミッション範囲を超えた時)
	};
	PlayerState pState = Nomal;
	HitObject m_characon;
	//ID3D11ShaderResourceView* g_nomalMapSRV = nullptr;


	struct Engin
	{
		SpriteEffect spriteeffect;
		CVector3 toEngin;
	};
	std::vector<Engin*> spriteeffect;
	ShaderResourceView m_srv;

	Level playerenginlevel;		//エンジンのポジションが入ったレベル

	missileRechargeHUD m_leftRechargeHUD;
	missileRechargeHUD m_riteRechargeHUD;
	HPGaugeHUD m_hpHUD;

};

