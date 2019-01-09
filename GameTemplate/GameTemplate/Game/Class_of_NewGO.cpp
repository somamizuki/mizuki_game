#include "stdafx.h"
#include "Class_of_NewGO.h"


Class_of_NewGO::Class_of_NewGO(int No, const char* obj_name):GameObject(No, obj_name)
{
	SDirectionLight sdir;		//ディレクションライトの構造体
	
	/*ディレクションライトをセット*/
	/*sdir.color = { 1.0f,1.0f,1.0f,1.0f };
	sdir.Direction = { 0.0f,-1.0f,0.0f,0.0f };
	m_dirlig.SetLight(sdir);*/
	
	/*ポイントライトをセット*/
	spoint.color= { 1.0f,1.0f,1.0f,1.0f };
	spoint.range = 8000000.0f;

	map = new sky(0,"map");
	map->Init(L"Assets/modelData/skyCubeMap.dds", L"Assets/modelData/sky.cmo", CVector3{ 4000000.0f,4000000.0f,4000000.0f });
	int enemyNo = 0;	/*エネミーの添字*/
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
		else if (std::wcscmp(Lobjdata.name, L"Sun") == 0)
		{
			Sun.Init(L"Assets/modelData/Sun.cmo");
			Sun.UpdateWorldMatrix(Lobjdata.position, CQuaternion::Identity(), CVector3::One());

			spoint.position = Lobjdata.position ;
			m_pointlig.SetLight(spoint,"sun");
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
	game_obj->DeleteGO(map);
	game_obj->DeleteGO(camera);
	game_obj->DeleteGO(player);
}

void Class_of_NewGO::Update()
{
	CVector3 pos = player->Getpos();
	SCamDir = CVector3(spoint.position.x, spoint.position.y, spoint.position.z) - pos;
	SCamDir.Normalize();
	map->SetPositon(CVector3::Zero());
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
		pos+(SCamDir*500.0f),
		pos
	);
	/*spoint.position.x += 10.0f;
	m_pointlig.Update(&spoint, "sun");*/
}

void Class_of_NewGO::Draw()
{
	level.Draw();
	Sun.Draw(
		PointLight,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}