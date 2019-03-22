#pragma once
#include "Player.h"
class BossEnemy :public GameObject
{
public:
	BossEnemy(int No, const char* obj_name);
	~BossEnemy();
	bool Start();
	void Update();
	void Draw();
	const CVector3& GetPos() const
	{
		return m_position;
	}
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	const CVector3& GetRight() const
	{
		return m_right;
	}
	const CVector3& GetUp() const
	{
		return m_up;
	}
	void SetPos(CVector3 position)
	{
		m_position = position;
	}


private:
	void Vector();
	void rotmanager();
	float Acos(float dotresult)				//���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���B
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}
	Animation m_animation;
	AnimationClip m_animationClip[1];
	SkinModel m_skinmodel;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	Player* m_player = nullptr;
	CVector3 m_right = CVector3::Right();
	CVector3 m_up = CVector3::Up();
	CVector3 m_forward = CVector3::Front();
	CVector3 m_playerpos = CVector3::Zero();
};

