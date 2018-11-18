#pragma once
#include "level/Level.h"
#include "Player.h"
#include"m_camera.h"
#include"Enemy.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"

class Class_of_NewGO:public GameObject
{
public:
	Class_of_NewGO(int No, const char* obj_name);
	~Class_of_NewGO();
	bool Start() { return true; }
	void Update();
	void Draw();
	std::vector<Enemy*>& GetEnemy()
	{
		return m_enemy;
	}

private:
	
	Player* player = nullptr;
	std::vector<Enemy*> m_enemy;
	Level *level = new Level;
	m_camera* camera;
	CDirectionLight m_dirlig;
	CPointLight m_pointlig;

};

