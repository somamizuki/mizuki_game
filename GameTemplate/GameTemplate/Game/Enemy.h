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
	/// エフェクトの描画
	/// </summary>
	void EffectDraw();
	/// <summary>
	/// 手前に描画したいものの描画
	/// </summary>
	void PostDraw();
	/// <summary>
	/// Delete時に呼ばれる関数
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// ポジションをセット
	/// </summary>
	/// <param name="pos">ポジション(CVector3)</param>
	void Setpos(CVector3 pos)						//エネミーのポジションをセット
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転をセット
	/// </summary>
	/// <param name="rot">回転(CQuaternion)</param>
	void Setrot(CQuaternion rot)					//エネミーの回転をセット
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 前方向
	/// </summary>
	/// <returns>前方向(CVector3)</returns>
	const CVector3& Getforward() const				//エネミーの前方向
	{
		return m_forward;
	}
	/// <summary>
	/// 右方向
	/// </summary>
	/// <returns>右方向(CVector3)</returns>
	const CVector3& Getrite() const					//エネミーの右方向
	{
		return m_rite;
	}
	/// <summary>
	/// 上方向
	/// </summary>
	/// <returns>上方向(CVector3)</returns>
	const CVector3& Getup() const					//エネミーの上方向
	{
		return m_up;
	}
	/// <summary>
	/// エネミーのポジション
	/// </summary>
	/// <returns>ポジション(CVector3)</returns>
	const CVector3& Getpos() const					//エネミーの上方向
	{
		return m_position;
	}
	/// <summary>
	/// エネミーの移動速度
	/// </summary>
	/// <returns>移動速度(CVector3)</returns>
	const CVector3& Getmovespeed() const			//エネミーの上方向
	{
		return movespeed;
	}
	/// <summary>
	/// エネミーの回転
	/// </summary>
	/// <returns>回転(CQuaternion)</returns>
	const CQuaternion& GetRotation() const			//エネミーの回転クオータニオンを取得
	{
		return m_rotation;
	}

private:
	/// <summary>
	/// 前右上のベクトルを計算する関数
	/// </summary>
	void mathVector();
	/// <summary>
	/// エネミーの移動をする関数
	/// </summary>
	void enemyMove();
	/// <summary>
	/// スプライトの管理をする関数
	/// </summary>
	void SpriteManager();
	/// <summary>
	/// バレットマネージャー
	/// </summary>
	void bulletManager();
	/// <summary>
	/// プレイヤーの方向を任意の軸に垂直な平面上になおしたベクトルを求める関数
	/// </summary>
	CVector3 side_vec(CVector3 forward_or_rite);
	/// <summary>
	/// 任意の軸から見たプレイヤーの角度を求める関数
	/// </summary>
	float p_angle(CVector3 forward_or_rite);
	/// <summary>
	/// 回転方向を求める関数
	/// </summary>
	float rot_dir(CVector3 forward_or_rite);
	/// <summary>
	/// acosf()で、1.0fよりも大きい数を渡さないようにするためのラップ関数。
	/// </summary>
	/// <param name="t">内積結果(float)</param>
	/// <returns>float</returns>
	float Acos(float t)
	{
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
};

