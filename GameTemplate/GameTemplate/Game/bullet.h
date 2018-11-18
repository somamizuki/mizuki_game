#pragma once
#include"Player.h"
#include"Class_of_NewGO.h"
class bullet:public GameObject
{
public:
	bullet(int No, const char* obj_name);
	~bullet();

	bool Start();
	void Update();
	void Draw();

	const CVector3 Getpos() const
	{
		return bulletpos;
	}

	bool GetDeadf()
	{
		return dead;
	}

private:
	//‚½‚Ü
	SkinModel m_tama;
	CVector3 tamadir = CVector3::Zero();
	CVector3 bulletpos = CVector3::Zero();
	float bulletspeed = 0.0f;
	Player* m_player = nullptr;
	Class_of_NewGO* CoN = nullptr;
	std::vector<Enemy*> m_enemy;
	bool dead = false;

};

