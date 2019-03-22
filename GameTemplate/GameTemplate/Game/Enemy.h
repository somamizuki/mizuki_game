#pragma once
#include"ObjectInfo.h"
#include"SpriteEffect.h"
#include"level/Level.h"


class Player;
class Class_of_NewGO;
class bullet;
using namespace BulletInfo;
class Enemy :public GameObject
{
public:
	Enemy(int No, const char* obj_name);
	~Enemy();

	bool Start();
	void Update();
	void Draw();
	void EffectDraw();
	void PostDraw();
	void OnDestroy();
	void Setpos(CVector3 pos)						//エネミーのポジションをセット
	{
		m_position = pos;
	}
	void Setrot(CQuaternion rot)					//エネミーの回転をセット
	{
		m_rotation = rot;
	}
	const CVector3& Getforward() const				//エネミーの前方向
	{
		return m_forward;
	}
	const CVector3& Getrite() const					//エネミーの右方向
	{
		return m_rite;
	}
	const CVector3& Getup() const					//エネミーの上方向
	{
		return m_up;
	}

	const CVector3& Getpos() const					//エネミーの上方向
	{
		return m_position;
	}

	const CVector3& Getmovespeed() const			//エネミーの上方向
	{
		return movespeed;
	}

	const CQuaternion& GetRotation() const			//エネミーの回転クオータニオンを取得
	{
		return m_rotation;
	}

private:
	void mathVector();								//前右上のベクトルを計算する関数
	void enemyMove();								//エネミーの移動をする関数
	void SpriteManager();							//スプライトの管理をする関数
	void bulletManager();							//バレットマネージャー

	CVector3 side_vec(CVector3 forward_or_rite);	//プレイヤーの方向を任意の軸に垂直な平面上になおしたベクトルを求める関数
	float p_angle(CVector3 forward_or_rite);		//任意の軸から見たプレイヤーの角度を求める関数
	float rot_dir(CVector3 forward_or_rite);		//回転方向を求める関数
	float Acos(float t)					//acosf()で、1.0fよりも大きい数を
	{									//渡さないようにするためのラップ関数。
		t = min(1.0f, max(-1.0f, t));
		return t;
	}

	bool posinScreen = false;			//スプライトを描画するかどうかのフラグ
	bool EnemyMarkerDraw = false;		//エネミーのマーカーを描画するかのフラグ


	/*エネミーのデータ（モデル、ポジション、回転など）。*/
	SkinModel m_model;										//スキンモデル
	CVector3 m_position = CVector3::Zero();					//ポジション
	//CVector3 targetPos = CVector3::Zero();				//ターゲットのポジション
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	/*エネミーの前、右、上*/
	CVector3 m_forward = CVector3::Zero();			//前
	CVector3 m_rite = CVector3::Zero();				//右
	CVector3 m_up = CVector3::Zero();				//上

	CVector3 movespeed = CVector3::Zero();			//移動速度
	float speed = 0.0f;
	Player* m_player = nullptr;						//プレイヤーのポインター
	bool atack_f = false;							//攻撃フラグ
	//std::vector<enemybullet*> m_bullet;			//エネミーの弾の配列
	ShaderResourceView shaderResource;				//エネミーの位置表示スプライトのシェーダーリソース
	ShaderResourceView EnemyMarkerSRV;				//まとのシェーダーリソース

	sprite sprite_ins;					//エネミーの位置表示スプライト
	sprite EnemyMarkerSprite;			//マーカー
	Class_of_NewGO* CoN = nullptr;		//クラスオブニューゴーのポインター


	const float bulletspan = 3.0f;		//バレットを発射する間隔
	float ritebulletTime = 0.0f;		//右バレットのタイマー
	float leftbulletTime = 0.0f;		//左バレットのタイマー

	bullet* RiteBullet = nullptr;		//右ミサイルのポインター
	bullet* LeftBullet = nullptr;		//左ミサイルのポインター
	Level Enemy_EnginPos;				//エネミーのジェットのポジションが入った
	struct Engin						//スプライトエフェクトとジェットのポジションを持った構造体
	{
		SpriteEffect spriteeffect;
		CVector3 toEngin;
	};
	std::vector<Engin*> spriteeffect;	//Enginをlevelに登録された数だけ積むリスト(vector)
	ShaderResourceView m_srv;			//スプライトエフェクトに使うSRV
	/*std::function<void()> m_rightBulletDeleteGoListener;
	std::function<void()> m_leftBulletDeleteGoListener;*/
};

