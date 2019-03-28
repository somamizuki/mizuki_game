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
	/// <summary>
	/// エネミーのコンストラクタ
	/// </summary>
	/// <param name="No">優先度</param>
	/// <param name="obj_name">名前</param>
	Enemy(int No, const char* obj_name);
	/// <summary>
	/// エネミーのデストラクタ
	/// </summary>
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
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転をセット
	/// </summary>
	/// <param name="rot">回転(CQuaternion)</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 前方向
	/// </summary>
	/// <returns>前方向(CVector3)</returns>
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/// <summary>
	/// 右方向
	/// </summary>
	/// <returns>右方向(CVector3)</returns>
	const CVector3& GetRite() const
	{
		return m_rite;
	}
	/// <summary>
	/// 上方向
	/// </summary>
	/// <returns>上方向(CVector3)</returns>
	const CVector3& GetUp() const
	{
		return m_up;
	}
	/// <summary>
	/// エネミーのポジション
	/// </summary>
	/// <returns>ポジション(CVector3)</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// エネミーの移動速度
	/// </summary>
	/// <returns>移動速度(CVector3)</returns>
	const CVector3& GetMoveSpeed() const
	{
		return m_movespeed;
	}
	/// <summary>
	/// エネミーの回転
	/// </summary>
	/// <returns>回転(CQuaternion)</returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

private:
	/// <summary>
	/// 前右上のベクトルを計算する関数
	/// </summary>
	void Vector();
	/// <summary>
	/// エネミーの移動をする関数
	/// </summary>
	void EnemyMove();
	/// <summary>
	/// スプライトの管理をする関数
	/// </summary>
	void SpriteManager();
	/// <summary>
	/// バレットマネージャー
	/// </summary>
	void BulletManager();
	/// <summary>
	/// プレイヤーの方向を任意の軸に垂直な平面上になおしたベクトルを求める関数
	/// </summary>
	CVector3 SideVec(CVector3 forward_or_rite);
	/// <summary>
	/// 任意の軸から見たプレイヤーの角度を求める関数
	/// </summary>
	float ToPlayerAngle(CVector3 forward_or_rite);
	/// <summary>
	/// 回転方向を求める関数
	/// </summary>
	float RotDirection(CVector3 forward_or_rite);
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

	bool						m_posinscreen = false;					//スプライトを描画するかどうかのフラグ
	bool						m_enemymarkerdraw = false;				//エネミーのマーカーを描画するかのフラグ


	/*エネミーのデータ（モデル、ポジション、回転など）。*/
	SkinModel					m_skinmodel;							//スキンモデル
	CVector3					m_position = CVector3::Zero();			//ポジション
	CQuaternion					m_rotation = CQuaternion::Identity();	//回転
	/*エネミーの前、右、上*/
	CVector3					m_forward = CVector3::Zero();			//前
	CVector3					m_rite = CVector3::Zero();				//右
	CVector3					m_up = CVector3::Zero();				//上

	CVector3					m_movespeed = CVector3::Zero();			//移動速度
	float						m_nowspeed = 0.0f;
	Player*						m_player = nullptr;						//プレイヤーのポインター
	ShaderResourceView			m_outscreenenemySRV;					//エネミーの位置表示スプライトのシェーダーリソース
	ShaderResourceView			m_enemymarkerSRV;						//まとのシェーダーリソース

	sprite						m_outenemysprite;						//エネミーの位置表示スプライト
	sprite						m_enemymarkersprite;					//マーカー
	Class_of_NewGO*				m_class_of_newgo = nullptr;				//クラスオブニューゴーのポインター


	const float					BULLETSPAN = 3.0f;						//バレットを発射する間隔
	float						m_ritebullettime = 0.0f;				//右バレットのタイマー
	float						m_leftbullettime = 0.0f;				//左バレットのタイマー

	bullet*						m_ritebullet = nullptr;					//右ミサイルのポインター
	bullet*						m_leftbullet = nullptr;					//左ミサイルのポインター
	Level						m_enemyenginlevel;						//エネミーのジェットのポジションが入った
	struct Engin	//スプライトエフェクトとジェットのポジションを持った構造体
	{
		SpriteEffect	m_spriteeffect;
		CVector3		m_toengin;
	};
	std::vector<Engin*>			m_spriteeffect;							//Enginをlevelに登録された数だけ積むリスト(vector)
	ShaderResourceView			m_effectsrv;							//スプライトエフェクトに使うSRV
};

