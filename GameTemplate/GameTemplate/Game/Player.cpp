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
	for (auto& tama : m_bullet)			//自分が消えると玉も消す。あっ、弾
	{
		game_obj->DeleteGO(tama);
	}
}

bool Player::Start()
{
	camera = game_obj->FindGO<m_camera>("camera");				//カメラのインスタンスを検索
	m_model.Init(L"Assets/modelData/StarSparrow.cmo");			//cmoファイルの読み込み。
	vector();				//プレイヤーの前右上のベクトルを計算する
	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/damage.dds");	//aim用のシェーダーリソースを作成
	aim.InitScreen2D(shaderResource, 0.0f, 0.0f,0.02f);			//aimを初期化
	return true;
}

void Player::playermove()
{
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	
	pad_X = g_pad[0].GetLStickXF();						//パッドの入力量を取得
	pad_Y = g_pad[0].GetLStickYF();

	
	movespeed = m_forward * defaultspeed;				//前方向にデフォルトスピードを
	if (g_pad[0].IsPress(enButtonB))					//Bボタンが押されたら
	{
		movespeed = m_forward * boostspeed;				//移動速度をブーストにする
	}
	if (g_pad[0].IsTrigger(enButtonA))					//Aボタンが押されたら
	{

		movespeed = m_forward * slowspeed;				//減速
	}

	/*
	回転
	*/
	rotX.SetRotationDeg(CVector3::AxisZ(), -pad_X* rotspeedX);		//マルチプライするので回転軸はワールドの軸でよい
	m_rotation.Multiply(rotX);
	rotY.SetRotationDeg(CVector3::AxisX(), pad_Y*rotspeedZ);		
	m_rotation.Multiply(rotY);

	/*
	エイムの微調整
	*/
	if (g_pad[0].IsPress(enButtonLB1))				//Lバンパーが押されたら
	{
		
		rotY.SetRotationDeg(CVector3::AxisY(), -bityousei);
		m_rotation.Multiply(rotY);
	}
	if (g_pad[0].IsPress(enButtonRB1))				//Rバンパーが押されたら
	{
		rotY.SetRotationDeg(CVector3::AxisY(), bityousei);
		m_rotation.Multiply(rotY);
	}

	vector();
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



void Player::Update()
{
	playermove();
	
	vector();
	m_position += movespeed * (1.0f / 60.0f);
	
	

	for (auto& tama : m_bullet)
	{
		float eraseLength = 20000.0f;
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() > eraseLength || tama->GetDeath_f())
		{
			game_obj->DeleteGO(tama);
			m_bullet.erase(std::remove(m_bullet.begin(), m_bullet.end(), tama), m_bullet.end());
			break;
		}
	}
	bool atack_f = true;
	for (auto& tama : m_bullet)
	{
		float atackLength = 2000.0f;
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() < atackLength)
		{
			atack_f = false;
		}
	}
	if (g_pad[0].IsTrigger(enButtonRB2) && atack_f == true)
	{
		m_bullet.push_back(new bullet(0, "bullet"));
	}
	
	
	
	//ワールド行列の更新。

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());


	

	CVector2 sptrans = CVector2(0.0f, 0.0f);
	CVector4 tmp = m_position + m_forward * (movespeed.Length()+bulletspeed);
	g_camera3D.GetViewMatrix().Mul(tmp);
	g_camera3D.GetProjectionMatrix().Mul(tmp);
	sptrans.x = tmp.x / tmp.w ;
	sptrans.y = tmp.y / tmp.w ;

	aim.Update(sptrans);
	
}
void Player::Draw()
{

	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostDraw()
{
	aim.Draw(
		*g_graphicsEngine->GetD3DDeviceContext()
	);
}