#include "stdafx.h"
#include "Player.h"
#include "Class_of_NewGO.h"
#include"math/kMath.h"
#include "m_camera.h"
#include"bullet.h"


namespace {
	const float MISSILE_RECHARGE_GAUGE_WIDTH = 170.0f;
	const float MISSILE_RECHARGE_GAUGE_HEIGHT = 15.0f;
	const float HP_GAUGE_WIDTH = 400.0f;
	const float HP_GAUGE_HEIGHT = 30.0f;
	const CVector3 MISSILE_RECHARGE_L_GAGE_POS = { -370.0f,-340.0f,0.0f };
	const CVector3 MISSILE_RECHARGE_R_GAGE_POS = { 370.0f- MISSILE_RECHARGE_GAUGE_WIDTH,-340.0f,0.0f };
	const CVector3 HP_GAUGE_POS = { 520.0f,470.0f,0.0f };
	
}
Player::Player(int No, const char* obj_name):GameObject(No, obj_name)
{	

}


Player::~Player()
{
	m_characon.RemoveRigidBoby();
}

bool Player::Start()
{
	camera = game_obj->FindGO<m_camera>("camera");				//カメラのインスタンスを検索
	camera->AddMyPointer<m_camera,Player>(&camera, this);
	CofNG = game_obj->FindGO<Class_of_NewGO>("newObject");		//エネミーたちのインスタンスを作ったクラスのポインターを検索
	CofNG->AddMyPointer<Class_of_NewGO, Player>(&CofNG, this);

	m_model.Init(L"Assets/modelData/StarSparrow.cmo");			//cmoファイルの読み込み。
	m_model.SetShadowReciever(true);							//影を受けるようにする。(セルフシャドウのため)

	
	m_model.SetNormalMap(L"Resource/sprite/StarSparrow_Normal.dds");//法線マップを適用

	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);	//シャドウキャスターに登録
	vector();				//プレイヤーの前右上のベクトルを計算する
	aimSRV.CreateFromDDSTextureFromFile(L"Resource/sprite/cursor.dds");	//aim用のシェーダーリソースを作成
	aimsprite.Init(aimSRV.GetBody(), 512.0f, 512.0f);			//aimを初期化
	LockOnSRV.CreateFromDDSTextureFromFile(L"Resource/sprite/mato.dds");
	LockOnSprite.Init(LockOnSRV.GetBody(), 512.0f, 512.0f);
	/*キャラコンの初期化*/
	m_characon.Init(m_position, m_rotation, 200.0f, 50.0f);
	/*バレットを配置*/
	LeftBullet = new bullet(0, "bullet");
	LeftBullet->WitchBullet(isPlayer);
	LeftBullet->SetLeft_or_Rite(Left);
	RiteBullet = new bullet(0, "bullet");
	RiteBullet->WitchBullet(isPlayer);
	RiteBullet->SetLeft_or_Rite(Rite);

	CVector3 pos;
	playerenginlevel.Init(L"Assets/level/Player_EnginPos.tkl", [&](LevelObjectData Lobjdata)
	{
		if (std::wcscmp(Lobjdata.name, L"StarSparrow") == 0)
		{
			pos = Lobjdata.position;
		}
		else if (std::wcscmp(Lobjdata.name, L"Box") == 0)
		{
			Engin* engin = new Engin;
			engin->toEngin = Lobjdata.position - pos;
			engin->toEngin = { CVector3::AxisX().Dot(engin->toEngin),CVector3::AxisY().Dot(engin->toEngin),CVector3::AxisZ().Dot(engin->toEngin) };
			spriteeffect.push_back(engin);
		}
		return true;
	});

	m_leftRechargeHUD.Init(L"Resource/sprite/missileGauge_waku.dds", L"Resource/sprite/missileGauge.dds", MISSILE_RECHARGE_GAUGE_WIDTH, MISSILE_RECHARGE_GAUGE_HEIGHT);
	m_riteRechargeHUD.Init(L"Resource/sprite/missileGauge_waku.dds", L"Resource/sprite/missileGauge.dds", MISSILE_RECHARGE_GAUGE_WIDTH, MISSILE_RECHARGE_GAUGE_HEIGHT);
	m_hpHUD.Init(L"Resource/sprite/missileGauge_waku.dds", L"Resource/sprite/missileGauge.dds", HP_GAUGE_WIDTH, HP_GAUGE_HEIGHT);
	m_srv.CreateFromDDSTextureFromFile(L"Resource/sprite/fog.dds");

	for (const auto& effct : spriteeffect)
	{
		effct->spriteeffect.Init(m_srv.GetBody(), 0.06f, 0);
	}

	return true;
}

Enemy* Player::LockOnManager()
{
	Enemy* LockOn_enemy = nullptr;		//ロックオンしたエネミーをさすポインター
	float dotresult = 0.0f;				//内積結果を入れる
	float dotresultMax = -2.0f;			//内積結果が最大のものを入れる
	CVector3 toEnemy = CVector3::Zero();//エネミーに向かうベクトル

	if (CofNG != nullptr)
	{
		for (const auto& enemy : CofNG->GetEnemy())
		{
			if (RiteBullet != nullptr)
			{
				enemy->RemoveHasMyPointerObject(RiteBullet);
			}
			if (LeftBullet != nullptr)
			{
				enemy->RemoveHasMyPointerObject(LeftBullet);
			}
			toEnemy = enemy->Getpos() - m_position;
			toEnemy.Normalize();
			dotresult = m_forward.Dot(toEnemy);
			float angle = CMath::RadToDeg(Acos(dotresult));
			float toEnemyLen = CVector3(enemy->Getpos() - m_position).Length();
			if (angle < 10.0f&&dotresult > dotresultMax&&toEnemyLen < 30000.0f)
			{
				dotresultMax = dotresult;
				LockOn_enemy = enemy;
				LockOnEnemyPos = enemy->Getpos();
			}
		}
		LockOnflag = false;
		if (LockOn_enemy != nullptr)
		{
			if (LockOn_enemy != prevLockOnEnemy)
			{
				if (CofNG->GetlockonSE()->IsPlaying())
				{
					CofNG->GetlockonSE()->Stop();
				}
				CofNG->GetlockonSE()->Play(false);
			}

			prevLockOnEnemy = LockOn_enemy;
			LockOnflag = true;
			if (prevLockOnEnemy->GetDeath_f())
			{
				prevLockOnEnemy = nullptr;
				LockOnflag = false;
			}

		}
		else
		{
			prevLockOnEnemy = nullptr;
		}
	}
	
	return LockOn_enemy;
}

void Player::playermove()
{
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	
	pad_X = g_pad[0].GetLStickXF();						//パッドの入力量を取得
	pad_Y = g_pad[0].GetLStickYF();

	
	
	if (g_pad[0].IsPress(enButtonRB2))					//Bボタンが押されたら
	{
		if (Speed < BoostSpeed)
		{
			Speed += 50.0f;			//移動速度をブーストにする
		}
	}
	else 
	{
		if (Speed > DefaultSpeed)
		{
			Speed -= 50.0f;
		}
		else
		{
			Speed += 50.0f;
		}
	}
	/*
	回転
	*/
	rotX.SetRotationDeg(CVector3::AxisZ(), -pad_X * RotSpeed_X);		//マルチプライするので回転軸はワールドの軸でよい
	m_rotation.Multiply(rotX);
	rotY.SetRotationDeg(CVector3::AxisX(), pad_Y * RotSpeed_Y);
	m_rotation.Multiply(rotY);

	/*
	エイムの微調整
	*/
	if (g_pad[0].IsPress(enButtonLB1))				//Lバンパーが押されたら
	{
		//回転
		rotY.SetRotationDeg(CVector3::AxisY(), -RotSpeed_Tw);
		m_rotation.Multiply(rotY);
	}
	if (g_pad[0].IsPress(enButtonRB1))				//Rバンパーが押されたら
	{
		//回転
		rotY.SetRotationDeg(CVector3::AxisY(), RotSpeed_Tw);
		m_rotation.Multiply(rotY);
	}

	vector();
	movespeed = m_forward * Speed;
}

void Player::playerreturn()
{
	movespeed = m_forward * DefaultSpeed;				//前方向にデフォルトスピードを
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	CVector3 mpos_to_zero = CVector3::Zero() - m_position;
	float flen = m_forward.Dot(mpos_to_zero);
	CVector3 fsidevec = mpos_to_zero - (m_forward * flen);
	fsidevec.Normalize();
	float fangle = CMath::RadToDeg(Acos(m_up.Dot(fsidevec)));
	if (m_rite.Dot(fsidevec)>0.0f)
	{
		rotX.SetRotationDeg(CVector3::AxisZ(), max(-RotSpeed_X, -fangle));		//マルチプライするので回転軸はワールドの軸でよい
		m_rotation.Multiply(rotX);
	}
	else if (m_rite.Dot(fsidevec) <= 0.0f)
	{
		rotX.SetRotationDeg(CVector3::AxisZ(), min(RotSpeed_X,fangle));		//マルチプライするので回転軸はワールドの軸でよい
		m_rotation.Multiply(rotX);
	}
	vector();
	mpos_to_zero = CVector3::Zero() - m_position;
	flen = m_forward.Dot(mpos_to_zero);
	fsidevec = mpos_to_zero - (m_forward * flen);
	fsidevec.Normalize();
	fangle = CMath::RadToDeg(Acos(m_up.Dot(fsidevec)));
	if (fangle < 1.0f || fsidevec.Length() == 0.0f)
	{
		mpos_to_zero = CVector3::Zero() - m_position;
		float rlen = m_rite.Dot(mpos_to_zero);
		CVector3 rsidevec = mpos_to_zero - (m_rite * rlen);
		rsidevec.Normalize();
		float rangle = CMath::RadToDeg(Acos(rsidevec.Dot(m_forward)));
		if (m_up.Dot(rsidevec) > 0.0f)
		{
			rotY.SetRotationDeg(CVector3::AxisX(), max(-RotSpeed_Y, -rangle));		//マルチプライするので回転軸はワールドの軸でよい
			m_rotation.Multiply(rotY);
		}
		else if (m_up.Dot(rsidevec) <= 0.0f)
		{
			rotY.SetRotationDeg(CVector3::AxisX(), min(RotSpeed_Y,rangle));		//マルチプライするので回転軸はワールドの軸でよい
			m_rotation.Multiply(rotY);
		}
	}
	vector();
}

void Player::vector()
{
	rot_M.MakeRotationFromQuaternion(m_rotation);	//クオータニオンから回転行列を作成
	m_rite.x = rot_M.m[0][0];
	m_rite.y = rot_M.m[0][1];
	m_rite.z = rot_M.m[0][2];
	m_up.x = rot_M.m[1][0];
	m_up.y = rot_M.m[1][1];
	m_up.z = rot_M.m[1][2];
	m_forward.x = rot_M.m[2][0];
	m_forward.y = rot_M.m[2][1];
	m_forward.z = rot_M.m[2][2];

	/*
	正規化
	*/
	m_forward.Normalize();
	m_rite.Normalize();
	m_up.Normalize();
}

void Player::bulletManager()
{
	Enemy* LockOnEnemy = LockOnManager();					//ロックオン
	if (RiteBullet != nullptr)
	{
		if (LockOnEnemy != nullptr)
		{
			LockOnEnemy->RemoveHasMyPointerObject(RiteBullet);
		}
		RiteBullet->SetTarget(LockOnEnemy);					//右側のミサイルをセット
	}
	if (LeftBullet != nullptr)
	{
		if (LockOnEnemy != nullptr)
		{
			LockOnEnemy->RemoveHasMyPointerObject(LeftBullet);
		}
		LeftBullet->SetTarget(LockOnEnemy);					//左側のミサイルをセット
	}

	if (RiteBullet == nullptr)
	{
		ritebulletTime += 1.0f*deltaTime;					//ミサイルがセットされていなければタイマーを進める
		ritemissileGaugelevel = min(1.0f, ritebulletTime / bulletspan);
	}

	if (ritebulletTime >= bulletspan &&RiteBullet==nullptr)
	{
		RiteBullet = new bullet(0, "bullet");				//右のミサイルをセット
		RiteBullet->WitchBullet(isPlayer);
		RiteBullet->SetTarget(LockOnEnemy);
		RiteBullet->SetLeft_or_Rite(Rite);
		ritebulletTime = 0.0f;

	}
	if (LeftBullet == nullptr)
	{
		leftbulletTime += 1.0f*deltaTime;					//ミサイルがセットされていなければタイマーを進める
		leftmissileGaugelevel = min(1.0f,leftbulletTime / bulletspan);
	}
	if (leftbulletTime >= bulletspan &&LeftBullet==nullptr)
	{
		LeftBullet = new bullet(0, "bullet");				//左のミサイルをセット
		LeftBullet->WitchBullet(isPlayer);
		LeftBullet->SetTarget(LockOnEnemy);
		LeftBullet->SetLeft_or_Rite(Left);
		leftbulletTime = 0.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA))
	{
		//ミサイルがセットされていれば撃つ
		if (RiteBullet!=nullptr)
		{
			if (CofNG != nullptr)
			{
				if (CofNG->GetfireSE()->IsPlaying())
				{
					CofNG->GetfireSE()->Stop();
				}
				CofNG->GetfireSE()->Play(false);
			}
			RiteBullet->SetBulletParam();
			RiteBullet = nullptr;
			ritemissileGaugelevel = 0.0f;
		}
		else if (LeftBullet!=nullptr)
		{
			if (CofNG != nullptr)
			{
				if (CofNG->GetfireSE()->IsPlaying())
				{
					CofNG->GetfireSE()->Stop();
				}
				CofNG->GetfireSE()->Play(false);
			}
			LeftBullet->SetBulletParam();
			LeftBullet = nullptr;
			leftmissileGaugelevel = 0.0f;
		}
	}
}

void Player::spritemanager()
{
	/*エイムスプライトのポジションを計算*/
	{
		CVector3 aimspritepos = m_position + (m_forward * 10000.0f);
		CMatrix wvp;
		wvp.MakeTranslation(aimspritepos);
		wvp.Mul(wvp, g_camera3D.GetViewMatrix());
		wvp.Mul(wvp, g_camera3D.GetProjectionMatrix());
		CVector3 SCpos = { wvp.m[3][0], wvp.m[3][1],wvp.m[3][2] };
		SCpos = SCpos / wvp.m[3][3];
		SCpos.x *= FRAME_BUFFER_W / 2.0f;
		SCpos.y *= FRAME_BUFFER_H / 2.0f;
		SCpos.z = 0.0f;
		aimsprite.Update(
			SCpos,
			CQuaternion::Identity(),
			CVector3::One()*0.08f
		);
	}
	/*ロックオンスプライトのポジションを計算*/
	{
		CMatrix wvp;
		wvp.MakeTranslation(LockOnEnemyPos);
		wvp.Mul(wvp, g_camera3D.GetViewMatrix());
		wvp.Mul(wvp, g_camera3D.GetProjectionMatrix());
		CVector3 LOEP = { wvp.m[3][0], wvp.m[3][1],wvp.m[3][2] };
		LOEP = LOEP / wvp.m[3][3];
		LOEP.x *= FRAME_BUFFER_W / 2.0f;
		LOEP.y *= FRAME_BUFFER_H / 2.0f;
		LOEP.z = 0.0f;
		LockOnSprite.Update(
			LOEP,
			CQuaternion::Identity(),
			CVector3::One()*0.2f
		);
	}
}

void Player::Update()
{
	switch (pState)
	{
	case Nomal:					//通常のプレイヤーの動き
	{
		playermove();
		break;
	}
	case Return:				//エリア外から帰還する際ののプレイヤーの動き
	{
		playerreturn();
		break;
	}
	}
	vector();
	
	if (CVector3(m_position - CVector3::Zero()).Length() > 100000.0f)
	{
		pState = Return;
	}
	else
	{
		pState = Nomal;
	}
	m_position = m_characon.Execute(deltaTime, movespeed, m_rotation);		
	bulletManager();
	

	if (m_playerParam.HP <= 0)
	{
		CofNG->GetEffect()->Play(m_position, CVector3::One()*100.0f);
		game_obj->DeleteGO(this);
	}
	
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);

	m_leftRechargeHUD.Update(MISSILE_RECHARGE_L_GAGE_POS, CQuaternion::Identity(), leftmissileGaugelevel);
	m_riteRechargeHUD.Update(MISSILE_RECHARGE_R_GAGE_POS, CQuaternion::Identity(), ritemissileGaugelevel);
	float HPGauge = m_playerParam.HP / HPMAX;
	m_hpHUD.Update(HP_GAUGE_POS, CQuaternion::Identity(), HPGauge);
	CofNG->GetResult()->SetRemHP(m_playerParam.HP);
	spritemanager();
}
/*
通常の描画
*/
void Player::Draw()
{
	//プレイヤーの描画
	m_model.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	
}

void Player::EffectDraw()
{
	for (const auto& effct : spriteeffect)
	{
		CVector3 pos = m_rite * effct->toEngin.x + m_up * effct->toEngin.y + m_forward * effct->toEngin.z;
		effct->spriteeffect.Update(m_position + pos);
		effct->spriteeffect.Draw();
	}
}



void Player::PostDraw()
{
	//スプライトの描画
	aimsprite.Draw(
		*g_graphicsEngine->GetD3DDeviceContext()
	);
	if (LockOnflag)
	{
		LockOnSprite.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
	
}

void Player::UIDraw()
{
	m_leftRechargeHUD.Draw();
	m_riteRechargeHUD.Draw();
	m_hpHUD.Draw();
}

void Player::OnDestroy()
{
	for (const auto& effct : spriteeffect)
	{
		delete effct;
	}
	spriteeffect.clear();
	if (RiteBullet != nullptr)
	{
		game_obj->DeleteGO(RiteBullet);
	}
	if (LeftBullet != nullptr)
	{
		game_obj->DeleteGO(LeftBullet);
	}
	/*game_obj->QueryGOs("bullet", [&](GameObject* go) {
		bullet* bl = (bullet*)go;
		bl->NotifyPlayerDead();
	});*/
}
