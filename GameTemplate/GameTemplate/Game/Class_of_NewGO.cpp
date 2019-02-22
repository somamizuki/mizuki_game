#include "stdafx.h"
#include "Class_of_NewGO.h"
#include "bullet.h"

Class_of_NewGO::Class_of_NewGO(int No, const char* obj_name):GameObject(No, obj_name)
{
	
}

Class_of_NewGO::~Class_of_NewGO()
{
	
}

bool Class_of_NewGO::Start()
{
	SDirectionLight sdir;		//ディレクションライトの構造体

	/*ディレクションライトをセット*/
	/*sdir.color = { 1.0f,0.95f,0.9f,1.0f };
	sdir.Direction = { 0.0f,0.0f,1.0f,0.0f };
	m_dirlig.SetLight(sdir);*/

	/*ポイントライトをセット*/
	float ligLuminance = 1.5f;
	spoint.color = { 1.0f,0.95f,0.9f,1.0f };
	spoint.color.x *= ligLuminance;
	spoint.color.y *= ligLuminance;
	spoint.color.z *= ligLuminance;

	spoint.range = 8000000.0f;

	map = new sky(0, "map");
	map->Init(L"Assets/modelData/skyCubeMap.dds", L"Assets/modelData/sky.cmo", CVector3{ 2000000.0f,2000000.0f,2000000.0f });
	
	level.Init(L"Assets/level/stage_02.tkl", [&](LevelObjectData Lobjdata) {

		if (std::wcscmp(Lobjdata.name, L"StarSparrow") == 0)
		{
			player = new Player(0, "player");
			player->AddMyPointer<Player, Class_of_NewGO>(&player,this);
			/*player->AddDeleteGOListeners([&](GameObject* go) {
				player = nullptr;
			});*/
			player->setposition(Lobjdata.position);
			player->setrot(Lobjdata.rotation);
		}
		else if (std::wcscmp(Lobjdata.name, L"Enemy") == 0)
		{
			Enemy*enemy = new Enemy(0, "enemy");
			enemy->AddMyPointer<Enemy, Class_of_NewGO >(&enemy,this);

			/*enemy->AddDeleteGOListeners([&](GameObject* go) {
				enemy = nullptr;
			});*/
			enemy->Setpos(Lobjdata.position);
			enemy->Setrot(Lobjdata.rotation);
			m_enemy.push_back(enemy);

		}
		else if (std::wcscmp(Lobjdata.name, L"Sun") == 0)
		{
			Sun.Init(L"Assets/modelData/Sun.cmo");
			Sun.UpdateWorldMatrix(Lobjdata.position, CQuaternion::Identity(), CVector3::One());

			spoint.position = Lobjdata.position;
			m_pointlig.SetLight(spoint, "sun");
		}
		else
		{
			return false;
		}
		return true;
	});
	camera = new m_camera(1, "camera");
	camera->AddMyPointer(&camera, this);

	/*サウンドの初期化*/
	m_soundEngine.Init();
	m_bgm.Init(L"Assets/sound/GameBGM4.wav");
	m_HitSE.Init(L"Assets/sound/HitSE.wav");
	m_lockonSE.Init(L"Assets/sound/lockonSE.wav");
	m_fireSE.Init(L"Assets/sound/fireSE.wav");
	m_bgm.SetVolume(0.5f);
	m_bgm.Play(true);
	return true;
}

void Class_of_NewGO::Update()
{
	if (player != nullptr)
	{
		pos = player->Getpos();
	}
	else
	{
		int a = 0;
	}
	if(player==nullptr)
	{
		if (g_pad[0].IsTrigger(enButtonA))
		{
			gameClear = true;
			Light_obj->DeleteLight(&m_pointlig);
		}
	}
	SCamDir = CVector3(spoint.position.x, spoint.position.y, spoint.position.z) - pos;
	SCamDir.Normalize();
	map->SetPositon(CVector3::Zero());
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
		pos+(SCamDir*500.0f),
		pos
	);
	if (m_enemy.size() == 0)
	{
		gameClear = true;
		Light_obj->DeleteLight(&m_pointlig);
	}
	m_soundEngine.Update();
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

void Class_of_NewGO::OnDestroy()
{
	for (auto& enemy : m_enemy)
	{
		game_obj->DeleteGO(enemy);
	}
	game_obj->DeleteGO(map);
	game_obj->DeleteGO(camera);
	game_obj->DeleteGO(player);
	/*game_obj->QueryGOs("bullet", [&](GameObject* go) {
		bullet* bl = (bullet*)go;
		bl->NotifyClass_Of_NewGODead();
	});*/
}
