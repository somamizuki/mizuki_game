#pragma once
#include "character/CharacterController.h"
#include"character/CharacterController.h"
#include"graphics/sprite.h"

class m_camera;
class Player:public GameObject
{
public:
	Player(int No, /*const*/ const char* obj_name);
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
	CMatrix rot_M;
	CVector3 m_forward;
	CVector3 m_rite;
	CVector3 m_up;
	CVector3 padinput_vector = CVector3::Zero();
	CQuaternion rot = CQuaternion::Identity();
	CVector3 padinput = CVector3::Zero();
	CVector3 move_vector = CVector3::Zero();			
	CharacterController m_characon;
	ShaderResourceView shaderResource;
	sprite sprite_ins;

	float m_angle = 0.0f;


	float pad_X = 0.0f;									//パッドXの入力量
	float pad_Y = 0.0f;									//パッドYの入力量


	enum m_state {
		move,
		stop
	};
	m_state move_or_stop = stop;						//動いてるかどうか
	void state_move();									//動いてる時
	void state_stop();									//止まっている時
	void Pad_Input();									//パッドの入力
	void vector();
	void Math();


	
	m_camera* camera = nullptr;
};

