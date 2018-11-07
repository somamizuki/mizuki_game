#include "stdafx.h"
#include "Class_of_NewGO.h"


Class_of_NewGO::Class_of_NewGO(int No, const char* obj_name):GameObject(No, obj_name)
{
	SDirectionLight sdir;
	sdir.color = { 1.0f,1.0f,1.0f,1.0f };
	sdir.Direction = { 0.0f,-1.0f,0.0f,0.0f };
	m_dirlig.SetLight(sdir);
	sdir.color = { 1.0f,0.0f,0.0f,1.0f };
	sdir.Direction = { 0.0f,1.0f,0.0f,0.0f };
	m_dirlig.SetLight(sdir);


	int enemyNo = 0;
	level->Init(L"Assets/level/stage_02.tkl", [&](LevelObjectData Lobjdata) {

		/*char* CPmodel_name = "unityChan";
		size_t char_size = strlen(CPmodel_name) + 1;
		wchar_t *WPmodel_name = new wchar_t[char_size];
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, WPmodel_name, char_size, CPmodel_name, _TRUNCATE);*/

		if (std::wcscmp(Lobjdata.name, L"StarSparrow"/*char_to_wchar_t("unityChan")*/) == 0)
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
	m_camera* camera = new m_camera(1, "camera");
}


Class_of_NewGO::~Class_of_NewGO()
{

}

void Class_of_NewGO::Update()
{

}

void Class_of_NewGO::Draw()
{
	level->Draw();
}