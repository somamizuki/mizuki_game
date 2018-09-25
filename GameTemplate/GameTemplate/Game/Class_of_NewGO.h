#pragma once
#include "level/Level.h"
#include "Player.h"
#include"m_camera.h"

class Class_of_NewGO:public GameObject
{
public:
	Class_of_NewGO(int No, const char* obj_name);
	~Class_of_NewGO();
	bool Start() { return true; }
	void Update();
	void Draw();

private:
	
	Player* player = nullptr;
	int i = 0;
	Level *level = new Level;
	m_camera* camera;
	
};

