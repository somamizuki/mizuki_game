#include "stdafx.h"
#include "Enemy.h"
#include"enemybullet.h"

Enemy::Enemy(int No, const char* obj_name):GameObject(No, obj_name)
{
}


Enemy::~Enemy()
{
	for (auto& tama : m_bullet)
	{
		game_obj->DeleteGO(tama);//自分が死んだら弾も消す
	}
}

bool Enemy::Start()
{
	m_player = game_obj->FindGO<Player>("player");			//プレイヤーを検索
	m_model.Init(L"Assets/modelData/Enemy.cmo");			//モデルのイニット
	m_model.SetShadowReciever(true);
	mathVector();											//前右上を計算
	/*スプライトのシェーダーリソースの作成*/
	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/EnemyPos.dds");
	matoshaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/mato.dds");
	/*スプライトの初期化*/
	sprite_ins.InitScreen2D(shaderResource, 0.0f, 0.0f, 0.1f);
	mato.InitScreen2D(matoshaderResource, 0.0f, 0.0f, 0.05f);
	return true;
}

void Enemy::mathVector()
{
	CMatrix m_Matrix = CMatrix::Identity();
	/*クオータニオンから回転行列を作成*/
	m_Matrix.MakeRotationFromQuaternion(m_rotation);
	/*回転行列から前右上を取得*/
	m_rite = { m_Matrix.m[0][0] ,m_Matrix.m[0][1] ,m_Matrix.m[0][2] };
	m_up = { m_Matrix.m[1][0] ,m_Matrix.m[1][1] ,m_Matrix.m[1][2] };
	m_forward = { m_Matrix.m[2][0] ,m_Matrix.m[2][1] ,m_Matrix.m[2][2] };
	/*正規化*/
	m_rite.Normalize();
	m_up.Normalize();
	m_forward.Normalize();

}



CVector3 Enemy::side_vec(CVector3 forward_or_rite)
{
	CVector3 e_to_p = CVector3::Zero();				//エネミーからプレイヤーに向かうベクトル
	CVector3 sideVec = CVector3::Zero();			//プレイヤーの方向を任意の軸に垂直な平面上になおしたベクトル
	float len = 0.0f;								//プレイヤーの位置を引数で受け取った軸に射影した際の長さ
	/*プレイヤーの位置といっても、正確には弾が到達した際にプレイヤーがいるであろう位置*/
	e_to_p = targetPos - m_position;
	len = forward_or_rite.Dot(e_to_p);
	sideVec = e_to_p - (forward_or_rite*len);
	sideVec.Normalize();

	return sideVec;
}

float Enemy::p_angle(CVector3 forward_or_rite)
{
	CVector3 e_to_p = targetPos - m_position;				//エネミーからプレイヤーに向かうベクトル
	e_to_p.Normalize();
	float acos_f = forward_or_rite.Dot(e_to_p);				//引数で受け取った軸とe_to_pのcosθを求める
	float angle = CMath::RadToDeg(acosf(Acos(acos_f)));		//アークcosして、θを求めてデグリーになおす(分りやすいから)
	
	return angle;
}

float Enemy::rot_dir(CVector3 forward_or_rite)
{
	CVector3 SV = side_vec(forward_or_rite);			//プレイヤーの方向を任意の軸に垂直な平面上になおしたベクトル
	

	float dir = 1.0f;		//回転方向
	/*受け取った軸が何なのかを判定している*/
	/*SVとの内積結果が0より大きいか小さいかで回転方向を決定する*/
	if (forward_or_rite.x == m_forward.x&&forward_or_rite.y == m_forward.y&&forward_or_rite.z == m_forward.z)
	{
		if (SV.Dot(m_rite) > 0.0f)
		{
			dir = -1.0f;
		}
		else if (SV.Dot(m_rite) < 0.0f)
		{
			dir = 1.0f;
		}
	}
	if (forward_or_rite.x == m_rite.x&&forward_or_rite.y == m_rite.y&&forward_or_rite.z == m_rite.z)
	{
		if (SV.Dot(m_forward) > 0.0f)
		{
			dir = 1.0f;
		}
		else if (SV.Dot(m_forward) < 0.0f)
		{
			dir = -1.0f;
		}
	}
	

	return dir;
}

void Enemy::enemyMove()
{
	//前横上の方向を更新
	mathVector();

	CVector3 e_to_p = CVector3::Zero();					//エネミーからプレイヤーに向かうベクトル
	CQuaternion rot = CQuaternion::Identity();			//回転
	float forwardrotangle = 0.0f;						//前軸周りに何度回転させるか
	float ritedrotangle = 0.0f;							//右軸周りに何度回転させるか
	float frotspeed = 0.0f;								//前軸周りの回転速度
	float rrotspeed = 0.0f;								//右軸周りの回転速度
	float rrotspeed_max = 1.0f;							//右軸周りの回転速度の最大値
	float frotspeed_max = 2.0f;							//前軸周りの回転速度の最大値
	

	/*ここはrrotspeed_maxをいい感じに調整しているだけ*/
	CVector3 p_to_e = m_position - m_player->Getpos();
	p_to_e.Normalize();
	float acos_f = m_player->Getforward().Dot(p_to_e);
	float angle = CMath::RadToDeg(acosf(Acos(acos_f)));
	rrotspeed_max = max(0.5f, min(1.5f,angle*(1.0f / 100.0f)));
	///////////////////////////////////////////////////////////


	
	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(side_vec(m_forward)))));
	frotspeed = min(frotspeed_max, forwardrotangle);

	rot.SetRotationDeg(CVector3::AxisZ(), frotspeed*rot_dir(m_forward));
	m_rotation.Multiply(rot);
	mathVector();

	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(side_vec(m_forward)))));
	if (forwardrotangle < 1.0f)
	{
		ritedrotangle = CMath::RadToDeg(acosf(Acos(m_forward.Dot(side_vec(m_rite)))));
		rrotspeed = min(rrotspeed_max, ritedrotangle/**(1.0f / max(1.0f,ritedrotangle))*/);

		rot.SetRotationDeg(CVector3::AxisX(), -rrotspeed);
		m_rotation.Multiply(rot);
		mathVector();
	}
	/*プレイヤーの前方向とプレイヤーから自分に向かうベクトルとの角度を求める*/
	p_to_e = m_position - m_player->Getpos();
	p_to_e.Normalize();
	acos_f = m_player->Getforward().Dot(p_to_e);
	angle = CMath::RadToDeg(acosf(Acos(acos_f)));

	e_to_p = m_player->Getpos() - m_position;
	/*まだ、数字が定まっていません。いろいろと*/
	if (p_angle(m_forward)<45.0f&&e_to_p.Length() < 4000.0f)
	{
		if (speed > m_player->Get_PlayerMove().Length() - 1000.0f)
		{
			speed -= 50.0f;
		}
	}
	else 
	{
		if (speed < 4000.0f)
		{
			speed += 50.0f;
		}
	}

	if (p_angle(m_forward) > 120.0f/*&&angle<30.0f*/)
	{
		if (speed < 8000.0f)
		{
			speed += 50.0f;

		}
	}
	else
	{
		if (speed > 4000.0f)
		{
			speed -= 50.0f;

		}
	}
	
	

	
	


	movespeed = m_forward * speed;
	m_position += movespeed * (1.0f / 60.0f);




	
}

void Enemy::SpriteManager()
{
	mathVector();
	
	//敵がいる方向を計算する
	CVector3 p_to_e = CVector3::Zero();
	CVector3 sideVec = CVector3::Zero();
	float len = 0.0f;
	p_to_e = m_position - m_player->Getpos();
	len = m_player->Getforward().Dot(p_to_e);
	sideVec = p_to_e - (m_player->Getforward()*len);
	sideVec.Normalize();
	//敵がいる方向を代入（一つは画面外にいるかどうかの判定用の変数）
	CVector2 sptrans = CVector2(0.0f, 0.0f);
	CVector2 inposf = CVector2(0.0f, 0.0f);
	CVector4 tmp = m_player->Getpos() + m_player->Getup()*100.0f + sideVec * 250.0f;
	CVector4 pos = m_player->Getpos() + m_player->Getup()*100.0f + p_to_e;
	//敵の方向をスクリーン座標系に変換
	g_camera3D.GetViewMatrix().Mul(tmp);
	g_camera3D.GetProjectionMatrix().Mul(tmp);
	sptrans.x = tmp.x / tmp.w;
	sptrans.y = tmp.y / tmp.w;
	//2Dの位置をアップデート
	sprite_ins.Update(sptrans);
	//敵が画面内にいるかの判定
	g_camera3D.GetViewMatrix().Mul(pos);
	g_camera3D.GetProjectionMatrix().Mul(pos);
	inposf.x = pos.x / pos.w;
	inposf.y = pos.y / pos.w;
	//trueなら画面外にいる
	if (inposf.x > 1.0f || inposf.y > 1.0f)
	{
		posinScreen = true;
	}
	if (inposf.x <= 1.0f && inposf.y <= 1.0f)
	{
		posinScreen = false;
	}
	p_to_e.Normalize();
	//プレイヤーの後ろにいれば強制的に画面外
	if (p_to_e.Dot(m_player->Getforward()) < 0.0f)
	{
		posinScreen = true;
	}

	


	//まとの位置を予測
	float speed = m_player->Get_PlayerMove().Length() + bulletspeed;
	p_to_e = m_position - m_player->Getpos();
	float yosoku_f = p_to_e.Length()*(1.0f / speed);
	CVector4 matopos = m_position + movespeed * yosoku_f;
	
	//まとの位置をスクリーン座標系に変換
	CVector2 matotrans= CVector2(0.0f, 0.0f);
	g_camera3D.GetViewMatrix().Mul(matopos);
	g_camera3D.GetProjectionMatrix().Mul(matopos);
	matotrans.x = matopos.x / matopos.w;
	matotrans.y = matopos.y / matopos.w;
	//まとの位置をアップデート
	mato.Update(matotrans);


	
}

void Enemy::Update()
{
	/*弾が到達した際にプレイヤーがいるであろう位置を予測*/
	float speed = movespeed.Length() + bulletspeed;							//弾の最終速度
	CVector3 e_to_p = m_player->Getpos() - m_position;						//エネミーからプレイヤーに向かうベクトル
	float yosoku_f = e_to_p.Length()*(1.0f / speed);						//弾が到達するまでの時間
	targetPos = m_player->Getpos() + m_player->Get_PlayerMove()*yosoku_f;
	
	atack_f = false;
	enemyMove();
	if (p_angle(m_forward)<2.0f)
	{
		/*プレイヤーが前方向2.0度以内にいたら撃つ*/
		atack_f = true;
	}

	for (auto& tama : m_bullet)
	{
		CVector3 to_bullet = tama->Getpos() - m_position;
		//弾をゆっくり撃つ処理
		if (to_bullet.Length() <= firelength)
		{
			atack_f = false;
		}
		//遠くなったら弾を消す
		if (to_bullet.Length() > eraselength)
		{
			game_obj->DeleteGO(tama);
			m_bullet.erase(std::remove(m_bullet.begin(), m_bullet.end(), tama), m_bullet.end());
		}
	}
	if (atack_f==true)
	{
		//弾を撃つ
		enemybullet* tama= new enemybullet(0, "enemybullet");
		tama->setpoint(this);
		m_bullet.push_back(tama);
	
	}




	SpriteManager();
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Enemy::Draw()
{
	m_model.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	
	
	
}

void Enemy::PostDraw()
{
	if (posinScreen == true)
	{
		sprite_ins.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
	else
	{
		mato.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
}