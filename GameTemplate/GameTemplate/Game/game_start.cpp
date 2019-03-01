#include "stdafx.h"
#include "game_start.h"


game_start::game_start(int No, const char* obj_name) :GameObject(No, obj_name)
{
}


game_start::~game_start()
{

}

bool game_start::Start()
{
	SDirectionLight sdir;		//ディレクションライトの構造体

	/*ポイントライトをセット*/
	spoint.color = { 1.0f*2.0f,0.95f*2.0f,0.9f*2.0f,1.0f };
	spoint.range = 8000000.0f;

	map = new sky(0, "map");
	map->Init(L"Assets/modelData/skyCubeMap.dds", L"Assets/modelData/sky.cmo", CVector3{ 500000.0f,500000.0f,500000.0f });
	level.Init(L"Assets/level/startlevel.tkl", [&](LevelObjectData Lobjdata)
	{
		if (std::wcscmp(Lobjdata.name, L"StarSparrow") == 0)
		{
			m_sikinmodel.Init(L"Assets/modelData/StarSparrow.cmo");
			m_position = Lobjdata.position;
			m_rotation = Lobjdata.rotation;
		}
		else if (std::wcscmp(Lobjdata.name, L"Sun") == 0)
		{
			spoint.position = Lobjdata.position;
			m_pointlig.SetLight(spoint, "sun");
		}
		else
		{
			return false;
		}
		return true;
	});

	m_sikinmodel.SetShadowReciever(true);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_sikinmodel);
	m_sikinmodel.SetNormalMap(L"Resource/sprite/StarSparrow_Normal.dds");
	camerapos = CVector3::Zero() + CVector3::AxisZ()*400.0f;
	g_camera3D.SetPosition(camerapos);
	g_camera3D.SetTarget(CVector3::Zero());
	g_camera3D.SetFar(800000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.SetUp(CVector3::Up());



	/*サウンドの初期化*/
	
	m_bgm.Init(L"Assets/sound/TitleBGM1.wav");
	m_selectSE.Init(L"Assets/sound/selectSE.wav");
	m_decisionSE.Init(L"Assets/sound/decisionSE.wav");
	m_bgm.SetVolume(0.5f);
	m_bgm.Play(true);
	return true;
}

void game_start::Update()
{
	if (!m_decisionSE.IsPlaying())
	{
		if (g_pad->IsTrigger(enButtonUp) || g_pad->IsTrigger(enButtonDown))
		{
			if (m_selectSE.IsPlaying())
			{
				m_selectSE.Stop();
			}
			m_selectSE.Play(false);
			switch (Select)
			{
			case start: {
				Select = howtocontrol;
				break;
			}
			case howtocontrol: {
				Select = start;
				break;
			}
			}
		}

		if (g_pad->IsTrigger(enButtonA))
		{
			m_decisionSE.Play(false);
			switch (Select)
			{
			case start: {
				startTimer = true;
				break;
			}
			case howtocontrol: {

			}
			}

		}
	}
	if (startTimer == true && !m_decisionSE.IsPlaying())
	{
		Light_obj->DeleteLight(&m_pointlig);
		game_obj->DeleteGO(map);
		gamestart = true;
	}

	
	SCamDir = CVector3(spoint.position.x, spoint.position.y, spoint.position.z) - m_position;
	SCamDir.Normalize();
	map->SetPositon(CVector3::Zero());
	g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(
		m_position + (SCamDir*1000.0f),
		m_position
	);
	m_sikinmodel.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	ligParam ligp;
	ligp.eyepos = camerapos;
	ligp.specPow = 50.0f;
	Light_obj->SetLightParam(ligp);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_sikinmodel);
	g_camera3D.Update();
	
}

void game_start::Draw()
{
	m_sikinmodel.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void game_start::UIDraw()
{
	switch (Select)
	{
	case start: {
		m_font.BeginDraw();
		m_font.Draw(L"GAME START", { 130.0f,0.0f }, SelectedStringColor,0.0f, 0.35f);
		m_font.Draw(L"HOW TO PLAY", { 130.0f,-150.0f }, noSelectStringColor, 0.0f, 0.35f);
		m_font.EndDraw();

		break;
	}
	case howtocontrol: {
		m_font.BeginDraw();
		m_font.Draw(L"GAME START", { 130.0f,0.0f }, noSelectStringColor, 0.0f, 0.35f);
		m_font.Draw(L"HOW TO PLAY", { 130.0f,-150.0f }, SelectedStringColor, 0.0f, 0.35f);
		m_font.EndDraw();
		break;
	}
	}
}

void game_start::OnDestroy()
{
}
