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

	/*CMatrix Getmatrix()
	{
		&m_model.FindBone()->GetWorldMatrix()
	}*/
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
	CharacterController m_characon;
	ShaderResourceView shaderResource;
	sprite sprite_ins;

	float m_angle = 0.0f;


	


	enum m_state {
		move,
		stop
	};
	m_state move_or_stop = stop;						//動いてるかどうか
	void playermove();
	void vector();
	void LightConf();


	
	m_camera* camera = nullptr;

	/*
	ライト
	*/
	/*std::vector<LightBase*> m_Light;
	ligParam ligp;
	SDirectionLight dirlightS[1];
	SPointLight pointlightS[25];
	SSpotLight spotlightS[1];
	int spot_f = 1;
	CVector3 colorV = CVector3::AxisZ();
	CQuaternion Crot1 = CQuaternion::Identity();
	CQuaternion Crot2 = CQuaternion::Identity();
	CQuaternion Crot3 = CQuaternion::Identity();
	CQuaternion Crot4 = CQuaternion::Identity();*/
	std::vector<bullet*> m_bullet;


	float sp_y = 0.0f;
	bool yf = true;

	
	/*ShaderResourceView* m_normal*/

};

