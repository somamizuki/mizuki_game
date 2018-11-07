#include "stdafx.h"
#include "Player.h"
#include"math/kMath.h"
#include "m_camera.h"
#include"bullet.h"


Player::Player(int No, const char* obj_name):GameObject(No, obj_name)
{	

}


Player::~Player()
{
}

bool Player::Start()
{



	/*
	ライトの初期化
	*/
	float len = 1000.0f;

	/*dirlightS[0].color = { 1.0f,1.0f,1.0f,1.0f };
	dirlightS[0].Direction = { 1.0f,-1.0f,0.0f,0.0f };

	pointlightS[0].color = { 1.0f,0.0f,0.0f,1.0f };
	pointlightS[0].position = { 2000.0f,200.0f,2000.0f,0.0f };
	pointlightS[0].range = len;
	pointlightS[1].color = { 1.0f,0.0f,0.0f,1.0f };
	pointlightS[1].position = { 1000.0f,200.0f,2000.0f,0.0f };
	pointlightS[1].range = len;
	pointlightS[2].color = { 1.0f,0.0f,0.0f,1.0f };
	pointlightS[2].position = { 0.0f,200.0f,2000.0f,0.0f };
	pointlightS[2].range = len;
	pointlightS[3].color = { 1.0f,0.0f,0.0f,1.0f };
	pointlightS[3].position = { -1000.0f,200.0f,2000.0f,0.0f };
	pointlightS[3].range = len;
	pointlightS[4].color = { 1.0f,0.0f,0.0f,1.0f };
	pointlightS[4].position = { -2000.0f,200.0f,2000.0f,0.0f };
	pointlightS[4].range = len;

	pointlightS[5].color = { 0.0f,1.0f,0.0f,1.0f };
	pointlightS[5].position = { 2000.0f,200.0f,1000.0f,0.0f };
	pointlightS[5].range = len;
	pointlightS[6].color = { 0.0f,1.0f,0.0f,1.0f };
	pointlightS[6].position = { 1000.0f,200.0f,1000.0f,0.0f };
	pointlightS[6].range = len;
	pointlightS[7].color = { 0.0f,1.0f,0.0f,1.0f };
	pointlightS[7].position = { 0.0f,200.0f,1000.0f,0.0f };
	pointlightS[7].range = len;
	pointlightS[8].color = { 0.0f,1.0f,0.0f,1.0f };
	pointlightS[8].position = { -1000.0f,200.0f,1000.0f,0.0f };
	pointlightS[8].range = len;
	pointlightS[9].color = { 0.0f,1.0f,0.0f,1.0f };
	pointlightS[9].position = { -2000.0f,200.0f,1000.0f,0.0f };
	pointlightS[9].range = len;

	pointlightS[10].color = { 0.0f,0.0f,1.0f,1.0f };
	pointlightS[10].position = { 2000.0f,200.0f,0.0f,0.0f };
	pointlightS[10].range = len;
	pointlightS[11].color = { 0.0f,0.0f,1.0f,1.0f };
	pointlightS[11].position = { 1000.0f,200.0f,0.0f,0.0f };
	pointlightS[11].range = len;
	pointlightS[12].color = { 0.0f,0.0f,1.0f,1.0f };
	pointlightS[12].position = { 0.0f,200.0f,0.0f,0.0f };
	pointlightS[12].range = len;
	pointlightS[13].color = { 0.0f,0.0f,1.0f,1.0f };
	pointlightS[13].position = { -1000.0f,200.0f,0.0f,0.0f };
	pointlightS[13].range = len;
	pointlightS[14].color = { 0.0f,0.0f,1.0f,1.0f };
	pointlightS[14].position = { -2000.0f,200.0f,0.0f,0.0f };
	pointlightS[14].range = len;

	pointlightS[15].color = { 0.0f,1.0f,1.0f,1.0f };
	pointlightS[15].position = { 2000.0f,200.0f,-1000.0f,0.0f };
	pointlightS[15].range = len;
	pointlightS[16].color = { 0.0f,1.0f,1.0f,1.0f };
	pointlightS[16].position = { 1000.0f,200.0f,-1000.0f,0.0f };
	pointlightS[16].range = len;
	pointlightS[17].color = { 0.0f,1.0f,1.0f,1.0f };
	pointlightS[17].position = { 0.0f,200.0f,-1000.0f,0.0f };
	pointlightS[17].range = len;
	pointlightS[18].color = { 0.0f,1.0f,1.0f,1.0f };
	pointlightS[18].position = { -1000.0f,200.0f,-1000.0f,0.0f };
	pointlightS[18].range = len;
	pointlightS[19].color = { 0.0f,1.0f,1.0f,1.0f };
	pointlightS[19].position = { -2000.0f,200.0f,-1000.0f,0.0f };
	pointlightS[19].range = len;

	pointlightS[20].color = { 1.0f,0.0f,1.0f,1.0f };
	pointlightS[20].position = { 2000.0f,200.0f,-2000.0f,0.0f };
	pointlightS[20].range = len;
	pointlightS[21].color = { 1.0f,0.0f,1.0f,1.0f };
	pointlightS[21].position = { 1000.0f,200.0f,-2000.0f,0.0f };
	pointlightS[21].range = len;
	pointlightS[22].color = { 1.0f,0.0f,1.0f,1.0f };
	pointlightS[22].position = { 0.0f,200.0f,-2000.0f,0.0f };
	pointlightS[22].range = len;
	pointlightS[23].color = { 1.0f,0.0f,1.0f,1.0f };
	pointlightS[23].position = { -1000.0f,200.0f,-2000.0f,0.0f };
	pointlightS[23].range = len;
	pointlightS[24].color = { 1.0f,0.0f,1.0f,1.0f };
	pointlightS[24].position = { -2000.0f,200.0f,-2000.0f,0.0f };
	pointlightS[24].range = len;



	spotlightS[0].color = { 1.0f,1.0f,1.0f,1.0f };
	spotlightS[0].Direction = { 0.0f,-1.0f,0.0f,0.0f };
	spotlightS[0].position = { 0.0f,1000.0f,0.0f,0.0f };
	spotlightS[0].SpotAngle = 7.0f;
	spotlightS[0].range = 20000.0f;


	m_Light.push_back(new LightBase);
	m_Light[0]->InitLight(&dirlightS,Direction,sizeof(dirlightS));
	m_Light.push_back(new LightBase);
	m_Light[1]->InitLight(&pointlightS,Point, sizeof(pointlightS));
	m_Light.push_back(new LightBase);
	m_Light[2]->InitLight(&spotlightS,Spot, sizeof(spotlightS));

	m_Light[0]->setspecf(true);*/





	camera = game_obj->FindGO<m_camera>("camera");
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/StarSparrow.cmo");
	


	rot_M.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = rot_M.m[2][0];
	m_forward.y = rot_M.m[2][1];
	m_forward.z = rot_M.m[2][2];
	m_rite.x = rot_M.m[0][0];
	m_rite.y = rot_M.m[0][1];
	m_rite.z = rot_M.m[0][2];
	m_up.x = rot_M.m[1][0];
	m_up.y = rot_M.m[1][1];
	m_up.z = rot_M.m[1][2];
	m_forward.Normalize();
	m_rite.Normalize();
	m_up.Normalize();
	m_characon.Init(
		100.0f,
		100.0f,
		m_position
	);

	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/damage.dds");
	sprite_ins.InitScreen2D(shaderResource, 0.0f, 0.0f,0.05f);
	return true;
}

void Player::playermove()
{
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	float pad_X;									//パッドXの入力量
	float pad_Y;									//パッドYの入力量
	pad_X = g_pad[0].GetLStickXF()*3.0f;
	pad_Y = g_pad[0].GetLStickYF()*3.0f;

	movespeed = m_forward * 2000.0f;
	if (g_pad[0].IsPress(enButtonB))
	{
		movespeed = m_forward * 6000.0f;
	}
	
	rotX.SetRotationDeg(CVector3::AxisZ(), -pad_X);
	m_rotation.Multiply(rotX);
	rotY.SetRotationDeg(CVector3::AxisX(), pad_Y);
	m_rotation.Multiply(rotY);
	if (g_pad[0].IsPress(enButtonLB1))
	{
		rotY.SetRotationDeg(CVector3::AxisY(), -0.7f);
		m_rotation.Multiply(rotY);
	}
	if (g_pad[0].IsPress(enButtonRB1))
	{
		rotY.SetRotationDeg(CVector3::AxisY(), 0.7f);
		m_rotation.Multiply(rotY);
	}



	/*movespeed.x = 0.0f;
	movespeed.z = 0.0f;
	movespeed += camera->Get_camerarite()*pad_X;
	movespeed += camera->GetXZ()*pad_Y;

	float modelangle = 0.0f;
	CVector3 modelrotAxis = CVector3::Zero();
	movedir += camera->Get_camerarite()*pad_X;
	movedir += camera->GetXZ()*pad_Y;
	movedir.Normalize();
	modelangle = CMath::RadToDeg(acosf(CVector3::AxisZ().Dot(movedir)));
	modelrotAxis.Cross(CVector3::AxisZ(), movedir);
	modelrotAxis.Normalize();
	m_rotation.SetRotationDeg(modelrotAxis, modelangle);*/
}

void Player::vector()
{
	rot_M.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = rot_M.m[2][0];
	m_forward.y = rot_M.m[2][1];
	m_forward.z = rot_M.m[2][2];
	m_rite.x = rot_M.m[0][0];
	m_rite.y = rot_M.m[0][1];
	m_rite.z = rot_M.m[0][2];
	m_up.x = rot_M.m[1][0];
	m_up.y = rot_M.m[1][1];
	m_up.z = rot_M.m[1][2];
	m_forward.Normalize();
	m_rite.Normalize();
	m_up.Normalize();
}

void Player::LightConf()
{
	/*Crot1.SetRotationDeg(CVector3::AxisY(), 2.0f);
	Crot1.Multiply(colorV);
	Crot2.SetRotationDeg(CVector3::AxisX(), 2.0f);
	Crot2.Multiply(colorV);
	Crot3.SetRotationDeg(CVector3::AxisZ(), 2.0f);
	Crot3.Multiply(colorV);

	dirlightS[0].color.x = colorV.x;
	dirlightS[0].color.y = colorV.y;
	dirlightS[0].color.z = colorV.z;*/
	

	/*Crot4.SetRotationDeg(CVector3::AxisY(), 2.0f);
	Crot4.Multiply(dirlightS[0].Direction);*/

	/*spotlightS[0].Direction.x = m_position.x - spotlightS[0].position.x;
	spotlightS[0].Direction.y = m_position.y - spotlightS[0].position.y;
	spotlightS[0].Direction.z = m_position.z - spotlightS[0].position.z;

	ligp.eyepos = camera->GetPos();
	ligp.specPow = 50.0f;

	m_Light[0]->LightUpdateSubresource(&dirlightS);
	m_Light[0]->SetlightParam(ligp);
	m_Light[1]->LightUpdateSubresource(&pointlightS);
	m_Light[2]->LightUpdateSubresource(&spotlightS);*/
}

void Player::Update()
{
	
	playermove();

	LightConf();




	
	/*movespeed.y -= 9.8f;*/
	vector();
	m_position = m_characon.Execute(1.0f/60.0f, movespeed);
	bool atack_f = true;
	for (auto& tama : m_bullet)
	{
		CVector3 to_bullet = m_position - tama->Getpos();
		if (to_bullet.Length() <= 1500.0f)
		{
			atack_f = false;
		}
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() > 50000.0f)
		{
			game_obj->DeleteGO(tama);
			m_bullet.erase(std::remove(m_bullet.begin(), m_bullet.end(), tama), m_bullet.end());
		}
	}
	
	if (g_pad[0].IsTrigger(enButtonRB2)&& atack_f==true)
	{
		m_bullet.push_back(new bullet(0, "bullet"));
	}
	
	
	//ワールド行列の更新。

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());

	/*if (yf == true)
	{
		if (sp_y <= 1.0f)
		{
			sp_y += 0.017f;
		}
		else
		{
			yf = false;
		}
	}
	if (yf == false) 
	{
		if (sp_y >= -1.0f)
		{
			sp_y -= 0.017f;
		}
		else {
			yf = true;
		}
	}*/

	

	CVector2 sptrans = CVector2(0.0f, 0.0f);
	CVector4 tmp = m_position + m_up * 100.0f + m_forward * 500.0f;
	g_camera3D.GetViewMatrix().Mul(tmp);
	g_camera3D.GetProjectionMatrix().Mul(tmp);
	sptrans.x = tmp.x / tmp.w ;
	sptrans.y = tmp.y / tmp.w ;

	sprite_ins.Update(sptrans);
	
}
void Player::Draw()
{
	
	/*m_Light[0]->SendConstantBuffer();
	m_Light[1]->SendConstantBuffer();
	m_Light[2]->SendConstantBuffer();*/

	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	sprite_ins.Draw(
		*g_graphicsEngine->GetD3DDeviceContext()
	);
}