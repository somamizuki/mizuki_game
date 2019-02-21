#pragma once
#include "Enemy.h"
#include "ObjectInfo.h"

using namespace BulletInfo;
class enemybullet:public GameObject
{
public:
	enemybullet(int No, const char* obj_name);
	~enemybullet();
	bool Start();
	void Update();
	void Draw();
	void setpoint(Enemy* ene)
	{
		m_enemy = ene;
	}

	const CVector3 Getpos() const
	{
		return bulletpos;
	}

private:
	//‚½‚Ü
	SkinModel m_tama;
	CVector3 tamadir = CVector3::Zero();
	CVector3 bulletpos = CVector3::Zero();
	float speed = 0.0f;
	Enemy* m_enemy = nullptr;
};

