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
	bool Start();
	void Update();
	void Draw();
	void setposition(CVector3 pos)
	{
		m_position = pos;
	}
	void setrot(CQuaternion rot)
	{
		m_rotation = rot;
	}
	const CVector3& Getpos() const
	{
		return m_position;
	}

	const CVector3& Getforward() const
	{
		return m_forward;
	}

	const CVector3& Getrite() const
	{
		return m_rite;
	}

	const CVector3& Getup() const
	{
		return m_up;
	}

	const CVector3& Get_PlayerMove() const
	{
		return movespeed;
	}

	
private:
	SkinModel m_model;									//スキンモデル。

	

	CVector3 m_position = CVector3::Zero();				//プレイヤーのポジション
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 movespeed = CVector3::Zero();				//movespeed
	CVector3 movedir = CVector3::Zero();
	CMatrix rot_M;
	CVector3 m_forward;
	CVector3 m_rite;
	CVector3 m_up;
	CQuaternion rot = CQuaternion::Identity();
	ShaderResourceView shaderResource;
	sprite sprite_ins;

	float m_angle = 0.0f;

	void playermove();
	void vector();

	m_camera* camera = nullptr;

	std::vector<bullet*> m_bullet;


	float sp_y = 0.0f;
	bool yf = true;
	
	int atack_counter = 0;
};

