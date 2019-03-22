#include "stdafx.h"
#include "Class_of_NewGO.h"
#include "bullet.h"

Class_of_NewGO::Class_of_NewGO(int No, const char* obj_name) :GameObject(No, obj_name)
{

}

Class_of_NewGO::~Class_of_NewGO()
{

}

bool Class_of_NewGO::Start()
{
	//SDirectionLight sdir;		//ディレクションライトの構造体

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
	map->Init(L"Assets/modelData/skyCubeMap.dds", L"Assets/modelData/sky.cmo", CVector3{ 1000000.0f,1000000.0f,1000000.0f });

	level.Init(L"Assets/level/stage.tkl", [&](LevelObjectData Lobjdata) {

		if (std::wcscmp(Lobjdata.name, L"StarSparrow") == 0)
		{
			player = new Player(0, "player");
			player->AddMyPointer<Player, Class_of_NewGO>(&player, this);
			/*player->AddDeleteGOListeners([&](GameObject* go) {
				player = nullptr;
			});*/
			player->setposition(Lobjdata.position);
			player->setrot(Lobjdata.rotation);
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
	///*サウンドの初期化*/
	m_bgm.Init(L"Assets/sound/GameBGM4.wav");
	m_bgmendwave.Init(L"Assets/sound/GameBGM2.wav");
	m_HitSE.Init(L"Assets/sound/HitSE.wav");
	m_lockonSE.Init(L"Assets/sound/lockonSE.wav");
	m_fireSE.Init(L"Assets/sound/fireSE.wav");
	m_bgm.SetVolume(0.5f);
	m_bgm.Play(true);
	m_effect.Init(L"Assets/effect/CosmicMist.efk");
	return true;
}

void Class_of_NewGO::Update()
{
	if (m_enemy.size() == 0)
	{
		switch (WaveCounter)
		{
		case 1:
		{
			level.Init(L"Assets/level/Wave1_EnemyPos.tkl", [&](LevelObjectData Lobjdata) {

				if (std::wcscmp(Lobjdata.name, L"Enemy") == 0)
				{
					Enemy*enemy = new Enemy(0, "enemy");
					CVector3 enemypos = player->Getpos() + (player->Getrite()*Lobjdata.position.x + player->Getup()*Lobjdata.position.y + player->Getforward()*Lobjdata.position.z);

					enemy->Setpos(enemypos);
					enemy->Setrot(Lobjdata.rotation);
					m_enemy.push_back(enemy);


				}
				return true;
			});
			WaveCounter = 4;
			break;
		}
		case 2:
		{
			level.Init(L"Assets/level/Wave2_EnemyPos.tkl", [&](LevelObjectData Lobjdata) {

				if (std::wcscmp(Lobjdata.name, L"Enemy") == 0)
				{
					Enemy*enemy = new Enemy(0, "enemy");
					CVector3 enemypos = player->Getpos() + (player->Getrite()*Lobjdata.position.x + player->Getup()*Lobjdata.position.y + player->Getforward()*Lobjdata.position.z);

					enemy->Setpos(enemypos);
					enemy->Setrot(Lobjdata.rotation);
					m_enemy.push_back(enemy);

				}
				return true;
			});
			WaveCounter++;
			break;
		}
		case 3:
		{
			level.Init(L"Assets/level/Wave3_EnemyPos.tkl", [&](LevelObjectData Lobjdata) {

				if (std::wcscmp(Lobjdata.name, L"Enemy") == 0 && m_enemy.size() < 5)
				{
					Enemy*enemy = new Enemy(0, "enemy");
					CVector3 enemypos = player->Getpos() + (player->Getrite()*Lobjdata.position.x + player->Getup()*Lobjdata.position.y + player->Getforward()*Lobjdata.position.z);

					enemy->Setpos(enemypos);
					enemy->Setrot(Lobjdata.rotation);
					m_enemy.push_back(enemy);

				}
				return true;
			});
			WaveCounter++;
			if (m_bgm.IsPlaying())
			{
				m_bgm.Stop();
			}

			m_bgmendwave.Play(true);
			break;
		}
		case 4: {
			if (m_bossenemy == nullptr)
			{
				m_bossenemy = new BossEnemy(0, "bossenemy");
				m_bossenemy->AddMyPointer<BossEnemy, Class_of_NewGO>(&m_bossenemy, this);
			}
				

			WaveCounter++;
			break;
		}
		default:break;
		}
		for (auto& enemy : m_enemy)
		{
			enemy->AddMyPointer<Enemy, Class_of_NewGO>(&enemy, this);
		}
	}
	std::list<Enemy*> enemyDletelist;
	for (const auto& enemy : m_enemy)
	{
		if (enemy == nullptr)
		{
			enemyDletelist.push_back(enemy);
		}
	}
	bool deleteflag = false;
	for (const auto& deleteenemy : enemyDletelist)
	{
		for (const auto& enemy : m_enemy)
		{
			if (deleteenemy == enemy)
			{
				m_enemy.erase(std::remove(m_enemy.begin(), m_enemy.end(), enemy), m_enemy.end());

				break;
			}
		}
		deleteflag = true;
	}
	if (deleteflag == true)
	{
		/*コピー先のポインタをaddしなおす*/
		for (auto& nextenemyit : m_enemy)
		{
			nextenemyit->RemoveHasMyPointerObject(this);
			nextenemyit->AddMyPointer<Enemy, Class_of_NewGO>(&nextenemyit, this);
		}
	}


	if (player != nullptr)
	{
		pos = player->Getpos();
	}
	if (player == nullptr)
	{
		m_timer.Stop();
		m_result.SetRemMIN(m_timer.GetMIN());
		m_result.SetRemSEC(m_timer.GetSEC());
		ResultDrawFlag = true;
		if (g_pad[0].IsTrigger(enButtonB))
		{
			gameClear = true;
			Light_obj->DeleteLight(&m_pointlig);
		}
	}

	SCamDir = CVector3(spoint.position.x, spoint.position.y, spoint.position.z) - pos;
	SCamDir.Normalize();
	map->SetPositon(CVector3::Zero());
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
		pos + (SCamDir*500.0f),
		pos
	);

	m_timer.Update();
	if (m_timer.IsTIMEUP())
	{
		game_obj->DeleteGO(player);
		m_result.SetTimeUP(true);
		ResultDrawFlag = true;
		if (g_pad[0].IsTrigger(enButtonB))
		{
			gameClear = true;
			Light_obj->DeleteLight(&m_pointlig);
		}
	}
	/*リザルトを出す条件*/
	if (WaveCounter > 4 && m_enemy.size() <= 0 && m_bossenemy == nullptr)
	{
		m_timer.Stop();
		m_result.SetRemMIN(m_timer.GetMIN());
		m_result.SetRemSEC(m_timer.GetSEC());
		m_result.SetGameClear(true);
		ResultDrawFlag = true;
		if (g_pad[0].IsTrigger(enButtonB))
		{
			gameClear = true;
			Light_obj->DeleteLight(&m_pointlig);
		}
	}
	m_effect.Update();
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

void Class_of_NewGO::EffectDraw()
{
	m_effect.Draw();
}

void Class_of_NewGO::UIDraw()
{
	m_timer.Draw();
	if (ResultDrawFlag) m_result.Draw();

}

void Class_of_NewGO::OnDestroy()
{
	game_obj->DeleteGO(m_bossenemy);
	for (auto& enemy : m_enemy)
	{
		game_obj->DeleteGO(enemy);
	}
	m_enemy.clear();
	game_obj->DeleteGO(map);
	game_obj->DeleteGO(camera);
	game_obj->DeleteGO(player);
	/*game_obj->QueryGOs("bullet", [&](GameObject* go) {
		bullet* bl = (bullet*)go;
		bl->NotifyClass_Of_NewGODead();
	});*/
}
