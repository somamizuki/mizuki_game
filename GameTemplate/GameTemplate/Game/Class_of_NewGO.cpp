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
	m_spointlight.color = { 1.0f,0.95f,0.9f,1.0f };
	m_spointlight.color.x *= ligLuminance;
	m_spointlight.color.y *= ligLuminance;
	m_spointlight.color.z *= ligLuminance;

	m_spointlight.range = 8000000.0f;
	/*キューブマップのイニット*/
	m_cubemap = new sky(0, "map");
	m_cubemap->Init(L"Assets/modelData/skyCubeMap.dds", L"Assets/modelData/sky.cmo", CVector3{ 1000000.0f,1000000.0f,1000000.0f });

	m_level.Init(L"Assets/level/stage.tkl", [&](LevelObjectData Lobjdata) {

		if (std::wcscmp(Lobjdata.name, L"StarSparrow") == 0)
		{
			m_player = new Player(0, "player");
			m_player->AddMyPointer<Player, Class_of_NewGO>(&m_player, this);
			m_player->SetPosition(Lobjdata.position);
			m_player->SetRotation(Lobjdata.rotation);
		}
		else if (std::wcscmp(Lobjdata.name, L"Sun") == 0)
		{
			m_sun.Init(L"Assets/modelData/Sun.cmo");
			m_sun.UpdateWorldMatrix(Lobjdata.position, CQuaternion::Identity(), CVector3::One());

			m_spointlight.position = Lobjdata.position;
			m_pointlig.SetLight(m_spointlight, "sun");
		}
		else
		{
			return false;
		}
		return true;
	});
	/*カメラクラスのインスタンスを生成*/
	m_camera = new GameCamera(1, "camera");
	m_camera->AddMyPointer(&m_camera, this);
	/*サウンドの初期化*/
	m_bgm.Init(L"Assets/sound/GameBGM4.wav");
	m_bgmendwave.Init(L"Assets/sound/GameBGM2.wav");
	m_hitSE.Init(L"Assets/sound/HitSE.wav");
	m_lockonSE.Init(L"Assets/sound/lockonSE.wav");
	m_fireSE.Init(L"Assets/sound/fireSE.wav");
	m_bgm.SetVolume(0.5f);
	m_bgm.Play(true);
	/*エフェクトの初期化*/
	m_effect.Init(L"Assets/effect/CosmicMist.efk");
	return true;
}

void Class_of_NewGO::Update()
{
	/*Waveを管理*/
	if (m_enemy.size() == 0)
	{
		switch (m_wavecounter)
		{
		case 1:
		{
			m_level.Init(L"Assets/level/Wave1_EnemyPos.tkl", [&](LevelObjectData Lobjdata) {

				if (std::wcscmp(Lobjdata.name, L"Enemy") == 0)
				{
					Enemy*enemy = new Enemy(0, "enemy");
					CVector3 enemypos = m_player->GetPosition() + (m_player->GetRite()*Lobjdata.position.x + m_player->GetUp()*Lobjdata.position.y + m_player->GetForward()*Lobjdata.position.z);

					enemy->SetPosition(enemypos);
					enemy->SetRotation(Lobjdata.rotation);
					m_enemy.push_back(enemy);


				}
				return true;
			});
			m_wavecounter++;
			break;
		}
		case 2:
		{
			m_level.Init(L"Assets/level/Wave2_EnemyPos.tkl", [&](LevelObjectData Lobjdata) {

				if (std::wcscmp(Lobjdata.name, L"Enemy") == 0)
				{
					Enemy*enemy = new Enemy(0, "enemy");
					CVector3 enemypos = m_player->GetPosition() + (m_player->GetRite()*Lobjdata.position.x + m_player->GetUp()*Lobjdata.position.y + m_player->GetForward()*Lobjdata.position.z);

					enemy->SetPosition(enemypos);
					enemy->SetRotation(Lobjdata.rotation);
					m_enemy.push_back(enemy);

				}
				return true;
			});
			m_wavecounter++;
			break;
		}
		case 3:
		{
			m_level.Init(L"Assets/level/Wave3_EnemyPos.tkl", [&](LevelObjectData Lobjdata) {

				if (std::wcscmp(Lobjdata.name, L"Enemy") == 0 && m_enemy.size() < 10)
				{
					Enemy*enemy = new Enemy(0, "enemy");
					CVector3 enemypos = m_player->GetPosition() + (m_player->GetRite()*Lobjdata.position.x + m_player->GetUp()*Lobjdata.position.y + m_player->GetForward()*Lobjdata.position.z);

					enemy->SetPosition(enemypos);
					enemy->SetRotation(Lobjdata.rotation);
					m_enemy.push_back(enemy);

				}
				return true;
			});
			m_wavecounter++;
			if (m_bgm.IsPlaying())
			{
				m_bgm.Stop();
			}

			m_bgmendwave.Play(true);
			break;
		}
		/*case 4: {
			if (m_bossenemy == nullptr)
			{
				m_bossenemy = new BossEnemy(0, "bossenemy");
				m_bossenemy->AddMyPointer<BossEnemy, Class_of_NewGO>(&m_bossenemy, this);
			}


			WaveCounter++;
			break;
		}*/
		default:break;
		}
		for (auto& enemy : m_enemy)
		{
			enemy->AddMyPointer<Enemy, Class_of_NewGO>(&enemy, this);
		}
	}
	/*vectorはerase_removeイデオムでポインターのアドレスがコピーにより変わるため、それぞれのポインターを再び積みなおす。
	しなければDelete時にポインターにNULLが入らない。
	listですべき。
	ここでは実験的な意味も含めてあえてそのままにして解決策を考え実装している。*/
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
	/*ここまでが積みなおす処理*/

	if (m_player != nullptr)
	{
		m_playerposition = m_player->GetPosition();
	}
	if (m_player == nullptr)
	{
		m_timer.Stop();
		m_result.SetRemMIN(m_timer.GetMIN());
		m_result.SetRemSEC(m_timer.GetSEC());
		m_resultdrawflag = true;
		if (g_pad[0].IsTrigger(enButtonB))
		{
			m_gameclearflag = true;
			Light_obj->DeleteLight(&m_pointlig);
		}
	}

	m_lightcameradir = CVector3(m_spointlight.position.x, m_spointlight.position.y, m_spointlight.position.z) - m_playerposition;
	m_lightcameradir.Normalize();
	m_cubemap->SetPositon(CVector3::Zero());
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
		m_playerposition + (m_lightcameradir*500.0f),
		m_playerposition
	);

	m_timer.Update();
	if (m_timer.IsTIMEUP())
	{
		game_obj->DeleteGO(m_player);
		m_result.SetTimeUP(true);
		m_resultdrawflag = true;
		if (g_pad[0].IsTrigger(enButtonB))
		{
			m_gameclearflag = true;
			Light_obj->DeleteLight(&m_pointlig);
		}
	}
	/*リザルトを出す条件*/
	if (m_wavecounter > 3 && m_enemy.size() <= 0 /*&& m_bossenemy == nullptr*/)
	{
		m_timer.Stop();
		m_result.SetRemMIN(m_timer.GetMIN());
		m_result.SetRemSEC(m_timer.GetSEC());
		m_result.SetGameClear(true);
		m_resultdrawflag = true;
		if (g_pad[0].IsTrigger(enButtonB))
		{
			m_gameclearflag = true;
			Light_obj->DeleteLight(&m_pointlig);
		}
	}
	m_effect.Update();
}

void Class_of_NewGO::Draw()
{
	m_level.Draw();
	m_sun.Draw(
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
	if (m_resultdrawflag) m_result.Draw();

}

void Class_of_NewGO::OnDestroy()
{
	if (m_bossenemy != nullptr)
	{
		game_obj->DeleteGO(m_bossenemy);
	}

	for (auto& enemy : m_enemy)
	{
		game_obj->DeleteGO(enemy);
	}
	m_enemy.clear();
	game_obj->DeleteGO(m_cubemap);
	game_obj->DeleteGO(m_camera);
	game_obj->DeleteGO(m_player);
	/*game_obj->QueryGOs("bullet", [&](GameObject* go) {
		bullet* bl = (bullet*)go;
		bl->NotifyClass_Of_NewGODead();
	});*/
}
