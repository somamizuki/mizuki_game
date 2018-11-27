#pragma once
#include "character/CharacterController.h"
#include"character/CharacterController.h"
#include"graphics/sprite.h"
#include"Light/LightBase.h"
class m_camera;
class bullet;
class Player:public GameObject
{
public:
	Player(int No, const char* obj_name);
	~Player();
	bool Start();								//スタート関数
	void Update();								//アップデート関数
	void Draw();								//描画関数
	void PostDraw();							//手前に描画したいものの描画
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

	
private:
	SkinModel m_model;									//スキンモデル。

	

	CVector3 m_position = CVector3::Zero();				//プレイヤーのポジション
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 movespeed = CVector3::Zero();				//movespeed
	CMatrix rot_M;
	CVector3 m_forward;
	CVector3 m_rite;
	CVector3 m_up;
	ShaderResourceView shaderResource;
	sprite aim;

	float pad_X;									//パッドXの入力量
	float pad_Y;									//パッドYの入力量
	float defaultspeed = 4000.0f;					//デフォルトの速度
	float boostspeed = 8000.0f;						//ブースト時の速度
	float slowspeed = 2000.0f;						//スロースピード
	float rotspeedX = 2.0f;							//X軸周りの回転スピード
	float rotspeedZ = 2.0f;							//Z軸周りの回転スピード
	float bityousei = 0.3f;							//エイムを微調整する変数

	void playermove();								//プレイヤーの移動関数
	void vector();									//プレイヤーの前右上のベクトルを計算する関数

	m_camera* camera = nullptr;						//カメラのポインター

	std::vector<bullet*> m_bullet;					//玉の配列
};

