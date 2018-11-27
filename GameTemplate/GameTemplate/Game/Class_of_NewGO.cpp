#include "stdafx.h"
#include "Class_of_NewGO.h"


Class_of_NewGO::Class_of_NewGO(int No, const char* obj_name):GameObject(No, obj_name)
{
	SDirectionLight sdir;
	SPointLight spoint;

	sdir.color = { 1.0f,1.0f,1.0f,1.0f };
	sdir.Direction = { 0.0f,-1.0f,0.0f,0.0f };
	m_dirlig.SetLight(sdir);
	sdir.color = { 1.0f,0.0f,0.0f,1.0f };
	sdir.Direction = { 0.0f,1.0f,0.0f,0.0f };
	m_dirlig.SetLight(sdir);
	spoint.color= { 1.0f,0.0f,0.0f,1.0f };
	spoint.position= { 0.0f,100.0f,0.0f,0.0f };
	spoint.range = 1000.0f;
	m_pointlig.SetLight(spoint);


	int enemyNo = 0;
	level.Init(L"Assets/level/stage_02.tkl", [&](LevelObjectData Lobjdata) {

		

		if (std::wcscmp(Lobjdata.name, L"StarSparrow") == 0)
		{
			player=new Player(0, "player");
			player->setposition(Lobjdata.position);
			player->setrot(Lobjdata.rotation);
		}
		else if (std::wcscmp(Lobjdata.name, L"Enemy")==0)
		{
			m_enemy.push_back(new Enemy(0, "enemy"));
			m_enemy[enemyNo]->Setpos(Lobjdata.position);
			m_enemy[enemyNo]->Setrot(Lobjdata.rotation);
			enemyNo++;
		}
		else
		{
			return false;
		}
		return true;
	});
	camera = new m_camera(1, "camera");
}


Class_of_NewGO::~Class_of_NewGO()
{
	for (auto& enemy : m_enemy)
	{
		game_obj->DeleteGO(enemy);
	}
	game_obj->DeleteGO(camera);
	game_obj->DeleteGO(player);
}

void Class_of_NewGO::Update()
{

}

void Class_of_NewGO::Draw()
{
	level.Draw();
}