#pragma once
#include "Player.h"

class enemybullet;
class Enemy:public GameObject
{
public:
	Enemy(int No, const char* obj_name);
	~Enemy();

	bool Start();
	void Update();
	void Draw();
	void PostDraw();
	void Setpos(CVector3 pos)									//エネミーのポジションをセット
	{
		m_position = pos;
	}
	void Setrot(CQuaternion rot)								//エネミーの回転をセット
	{
		m_rotation = rot;
	}
	const CVector3& Getforward() const							//エネミーの前方向
	{
		return m_forward;
	}
	const CVector3& Getrite() const								//エネミーの右方向
	{
		return m_rite;
	}
	const CVector3& Getup() const								//エネミーの上方向
	{
		return m_up;
	}

	const CVector3& Getpos() const								//エネミーの上方向
	{
		return m_position;
	}

	const CVector3& Getmovespeed() const								//エネミーの上方向
	{
		return movespeed;
	}

private:

	void mathVector();
	void enemyMove();
	void SpriteManager();

	CVector3 side_vec(CVector3 forward_or_rite);  //プレイヤーの方向を任意の軸に垂直な平面上に直したもの
	float p_angle(CVector3 forward_or_rite);
	float rot_dir(CVector3 forward_or_rite);
	float Acos(float t)					//acosf()で、1.0fよりも大きい数を
	{									//渡さないようにするためのラップ関数。
		t = min(1.0f, max(-1.0f,t));
		return t;
	}

	bool posinScreen = false;
	

	/*エネミーのデータ（モデル、ポジション、回転など）。*/
	SkinModel m_model;											//スキンモデル
	CVector3 m_position = CVector3::Zero();						//ポジション
	CVector3 targetPos = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();			//回転
	/*エネミーの前、右、上*/
	CVector3 m_forward = CVector3::Zero();						//前
	CVector3 m_rite = CVector3::Zero();							//右
	CVector3 m_up = CVector3::Zero();							//上

	CVector3 movespeed = CVector3::Zero();
	//float bulletspeed = 0.0f;
	Player* m_player = nullptr;
	bool atack_f = false;
	std::vector<enemybullet*> m_bullet;
	ShaderResourceView shaderResource;
	ShaderResourceView matoshaderResource;

	sprite sprite_ins;
	sprite mato;//まと
};

