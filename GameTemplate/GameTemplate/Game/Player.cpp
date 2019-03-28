#include "stdafx.h"
#include "Player.h"
#include "Class_of_NewGO.h"
#include"math/kMath.h"
#include "GameCamera.h"
#include"bullet.h"
#include "BossEnemy.h"


namespace {
	const float MISSILE_RECHARGE_GAUGE_WIDTH = 170.0f;
	const float MISSILE_RECHARGE_GAUGE_HEIGHT = 15.0f;
	const float HP_GAUGE_WIDTH = 400.0f;
	const float HP_GAUGE_HEIGHT = 30.0f;
	const CVector3 MISSILE_RECHARGE_L_GAGE_POS = { -370.0f,-340.0f,0.0f };
	const CVector3 MISSILE_RECHARGE_R_GAGE_POS = { 370.0f - MISSILE_RECHARGE_GAUGE_WIDTH,-340.0f,0.0f };
	const CVector3 HP_GAUGE_POS = { 520.0f,470.0f,0.0f };

}
Player::Player(int No, const char* obj_name) :GameObject(No, obj_name)
{

}


Player::~Player()
{
}
bool Player::Start()
{
	m_camera = game_obj->FindGO<GameCamera>("camera");							//カメラのインスタンスを検索
	m_camera->AddMyPointer<GameCamera, Player>(&m_camera, this);
	m_class_of_newgo = game_obj->FindGO<Class_of_NewGO>("newObject");					//エネミーたちのインスタンスを作ったクラスのポインターを検索
	m_class_of_newgo->AddMyPointer<Class_of_NewGO, Player>(&m_class_of_newgo, this);
	m_skinmodel.Init(L"Assets/modelData/StarSparrow.cmo");						//cmoファイルの読み込み。
	m_skinmodel.SetShadowReciever(true);										//影を受けるようにする。(セルフシャドウのため)
	m_skinmodel.SetNormalMap(L"Resource/sprite/StarSparrow_Normal.dds");		//法線マップを適用
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_skinmodel);			//シャドウキャスターに登録
	Vector();	//プレイヤーの前右上のベクトルを計算する
	m_aimSRV.CreateFromDDSTextureFromFile(L"Resource/sprite/cursor.dds");		//aim用のシェーダーリソースを作成
	m_aimsprite.Init(m_aimSRV.GetBody(), 512.0f, 512.0f);						//aimを初期化
	m_lockonSRV.CreateFromDDSTextureFromFile(L"Resource/sprite/mato.dds");	//ロックオン用のシェーダーリソースを作成
	m_lockonsprite.Init(m_lockonSRV.GetBody(), 512.0f, 512.0f);					//ロックオンスプライトを初期化
	/*キャラコンの初期化*/
	m_characon.Init(m_position, m_rotation, 200.0f, 50.0f);
	/*バレットを配置*/
	m_leftbullet = new bullet(0, "bullet");
	m_leftbullet->WitchBullet(isPlayer);
	m_leftbullet->SetLeft_or_Rite(Left);
	m_ritebullet = new bullet(0, "bullet");
	m_ritebullet->WitchBullet(isPlayer);
	m_ritebullet->SetLeft_or_Rite(Rite);
	/*ジェットエンジンのポジションを初期化*/
	CVector3 pos;
	m_playerenginlevel.Init(L"Assets/level/Player_EnginPos.tkl", [&](LevelObjectData Lobjdata)
	{
		if (std::wcscmp(Lobjdata.name, L"StarSparrow") == 0)
		{
			pos = Lobjdata.position;
		}
		else if (std::wcscmp(Lobjdata.name, L"Box") == 0)
		{
			Engin* engin = new Engin;
			engin->m_toengin = Lobjdata.position - pos;
			engin->m_toengin = { CVector3::AxisX().Dot(engin->m_toengin),CVector3::AxisY().Dot(engin->m_toengin),CVector3::AxisZ().Dot(engin->m_toengin) };
			m_spriteeffectlist.push_back(engin);
		}
		return true;
	});

	m_effectSRV.CreateFromDDSTextureFromFile(L"Resource/sprite/fog.dds");		//ジェットエンジンのスプライト用SRVを作成

	for (const auto& effct : m_spriteeffectlist)
	{
		effct->m_spriteeffect.Init(m_effectSRV.GetBody(), 0.06f, 0);
	}

	m_leftrechargeHUD.Init(L"Resource/sprite/missileGauge_waku.dds", L"Resource/sprite/missileGauge.dds", MISSILE_RECHARGE_GAUGE_WIDTH, MISSILE_RECHARGE_GAUGE_HEIGHT);
	m_riterechargeHUD.Init(L"Resource/sprite/missileGauge_waku.dds", L"Resource/sprite/missileGauge.dds", MISSILE_RECHARGE_GAUGE_WIDTH, MISSILE_RECHARGE_GAUGE_HEIGHT);
	m_hpHUD.Init(L"Resource/sprite/missileGauge_waku.dds", L"Resource/sprite/missileGauge.dds", HP_GAUGE_WIDTH, HP_GAUGE_HEIGHT);


	return true;
}

Enemy* Player::LockOnManager()
{
	Enemy* lockonenemy = nullptr;		//ロックオンしたエネミーをさすポインター
	float dotresult = 0.0f;				//内積結果を入れる
	float dotresultMax = -2.0f;			//内積結果が最大のものを入れる
	CVector3 toEnemy = CVector3::Zero();//エネミーに向かうベクトル

	if (m_class_of_newgo != nullptr)
	{
		for (const auto& enemy : m_class_of_newgo->GetEnemy())
		{
			if (m_ritebullet != nullptr)
			{
				enemy->RemoveHasMyPointerObject(m_ritebullet);
			}
			if (m_leftbullet != nullptr)
			{
				enemy->RemoveHasMyPointerObject(m_leftbullet);
			}
			toEnemy = enemy->GetPosition() - m_position;
			toEnemy.Normalize();
			dotresult = m_forward.Dot(toEnemy);
			float angle = CMath::RadToDeg(Acos(dotresult));
			float toEnemyLen = CVector3(enemy->GetPosition() - m_position).Length();
			if (angle < 10.0f&&dotresult > dotresultMax&&toEnemyLen < 30000.0f)
			{
				dotresultMax = dotresult;
				lockonenemy = enemy;
				m_lockonenemypos = enemy->GetPosition();
			}

		}
		m_lockonflag = false;
		if (lockonenemy != nullptr)
		{
			if (lockonenemy != m_prevlockonenemy)
			{
				/*前回のロックオンエネミーと同じでなければ音を鳴らす*/
				if (m_class_of_newgo->GetLockOnSE()->IsPlaying())
				{
					m_class_of_newgo->GetLockOnSE()->Stop();
				}
				m_class_of_newgo->GetLockOnSE()->Play(false);
			}

			m_prevlockonenemy = lockonenemy;
			m_lockonflag = true;
			if (m_prevlockonenemy->GetDeath_f())
			{
				m_prevlockonenemy = nullptr;
				m_lockonflag = false;
			}

		}
		else
		{
			m_prevlockonenemy = nullptr;
		}
	}

	return lockonenemy;
}

void Player::PlayerMove()
{
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();

	pad_X = g_pad[0].GetLStickXF();						//パッドの入力量を取得
	pad_Y = g_pad[0].GetLStickYF();



	if (g_pad[0].IsPress(enButtonRB2))					//Bボタンが押されたら
	{
		if (m_nowspeed < BOOSTSPEED)
		{
			m_nowspeed += 50.0f;			//移動速度をブーストにする
		}
	}
	else
	{
		if (m_nowspeed > DEFAULTSPEED)
		{
			m_nowspeed -= 50.0f;
		}
		else
		{
			m_nowspeed += 50.0f;
		}
	}
	/*
	回転
	*/
	rotX.SetRotationDeg(CVector3::AxisZ(), -pad_X * ROTSPEED_X);		//マルチプライするので回転軸はワールドの軸でよい
	m_rotation.Multiply(rotX);
	rotY.SetRotationDeg(CVector3::AxisX(), pad_Y * ROTSPEED_Y);
	m_rotation.Multiply(rotY);

	/*
	エイムの微調整
	*/
	if (g_pad[0].IsPress(enButtonLB1))				//Lバンパーが押されたら
	{
		//回転
		rotY.SetRotationDeg(CVector3::AxisY(), -ROTSPEED_TW);
		m_rotation.Multiply(rotY);
	}
	if (g_pad[0].IsPress(enButtonRB1))				//Rバンパーが押されたら
	{
		//回転
		rotY.SetRotationDeg(CVector3::AxisY(), ROTSPEED_TW);
		m_rotation.Multiply(rotY);
	}

	Vector();
	movespeed = m_forward * m_nowspeed;
}

void Player::PlayerReturn()
{
	movespeed = m_forward * DEFAULTSPEED;				//前方向にデフォルトスピードを
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	CVector3 mpos_to_zero = CVector3::Zero() - m_position;
	float flen = m_forward.Dot(mpos_to_zero);
	CVector3 fsidevec = mpos_to_zero - (m_forward * flen);
	fsidevec.Normalize();
	float fangle = CMath::RadToDeg(Acos(m_up.Dot(fsidevec)));
	if (m_rite.Dot(fsidevec) > 0.0f)
	{
		rotX.SetRotationDeg(CVector3::AxisZ(), max(-ROTSPEED_X, -fangle));		//マルチプライするので回転軸はワールドの軸でよい
		m_rotation.Multiply(rotX);
	}
	else if (m_rite.Dot(fsidevec) <= 0.0f)
	{
		rotX.SetRotationDeg(CVector3::AxisZ(), min(ROTSPEED_X, fangle));		//マルチプライするので回転軸はワールドの軸でよい
		m_rotation.Multiply(rotX);
	}
	Vector();
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
			rotY.SetRotationDeg(CVector3::AxisX(), max(-ROTSPEED_Y, -rangle));		//マルチプライするので回転軸はワールドの軸でよい
			m_rotation.Multiply(rotY);
		}
		else if (m_up.Dot(rsidevec) <= 0.0f)
		{
			rotY.SetRotationDeg(CVector3::AxisX(), min(ROTSPEED_Y, rangle));		//マルチプライするので回転軸はワールドの軸でよい
			m_rotation.Multiply(rotY);
		}
	}
	Vector();
}

void Player::BossFightInit()
{
	movespeed = CVector3::Zero();
	if (m_class_of_newgo != nullptr)
	{
		m_bossenemy = m_class_of_newgo->GetBossEnemy();
		m_bossenemy->AddMyPointer<BossEnemy, Player>(&m_bossenemy, this);
		CVector3 bosspos = m_position + ((m_forward*TOBOSSLENGTH) + (m_up*-BOSSHEIGHT));
		m_bossenemy->SetPos(bosspos);
		m_bosstoplayer = m_position - (bosspos + m_up * BOSSHEIGHT);

	}


	m_bossfightinitflag = true;
}

void Player::BossFightMove()
{
	pad_X = g_pad[0].GetLStickXF()*-1.0f;						//パッドの入力量を取得

	/*ボスの周りをまわる計算*/
	CQuaternion rot = CQuaternion::Identity();
	if (m_bossenemy != nullptr)m_bossposition = m_bossenemy->GetPos() + (m_up * BOSSHEIGHT);
	m_bosstoplayer = m_position - m_bossposition;
	CVector3 oldvector = m_bosstoplayer;
	rot.SetRotationDeg(m_up, pad_X);
	rot.Multiply(m_bosstoplayer);
	CVector3 newvector = m_bosstoplayer;
	movespeed = (newvector - oldvector)*(1.0f / deltaTime);
	CVector3 toBoss = m_bossposition - (m_position + movespeed * deltaTime);
	float flen = m_forward.Dot(toBoss);
	float rlen = m_rite.Dot(toBoss);
	toBoss = m_forward * flen + m_rite * rlen;
	toBoss.Normalize();
	float dotresult = m_forward.Dot(toBoss);
	float angle = Acos(dotresult);
	CVector3 axis;
	axis.Cross(m_forward, toBoss);
	axis.Normalize();
	if (m_up.Dot(axis) < -0.9f)angle *= -1.0f;

	rot.SetRotation(CVector3::AxisY(), angle);
	m_rotation.Multiply(rot);

	Vector();
}

void Player::Vector()
{
	CMatrix rot_M;
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

void Player::BulletManager()
{
	Enemy* LockOnEnemy = LockOnManager();					//ロックオン
	if (m_ritebullet != nullptr)
	{
		if (LockOnEnemy != nullptr)
		{
			LockOnEnemy->RemoveHasMyPointerObject(m_ritebullet);
		}
		m_ritebullet->SetTarget(LockOnEnemy);					//右側のミサイルをセット
	}
	if (m_leftbullet != nullptr)
	{
		if (LockOnEnemy != nullptr)
		{
			LockOnEnemy->RemoveHasMyPointerObject(m_leftbullet);
		}
		m_leftbullet->SetTarget(LockOnEnemy);					//左側のミサイルをセット
	}

	if (m_ritebullet == nullptr)
	{
		m_ritebullettime += 1.0f*deltaTime;					//ミサイルがセットされていなければタイマーを進める
		m_ritemissilegaugelevel = min(1.0f, m_ritebullettime / BULLETSPAN);
	}

	if (m_ritebullettime >= BULLETSPAN && m_ritebullet == nullptr)
	{
		m_ritebullet = new bullet(0, "bullet");				//右のミサイルをセット
		m_ritebullet->WitchBullet(isPlayer);
		m_ritebullet->SetTarget(LockOnEnemy);
		m_ritebullet->SetLeft_or_Rite(Rite);
		m_ritebullettime = 0.0f;

	}
	if (m_leftbullet == nullptr)
	{
		m_leftbullettime += 1.0f*deltaTime;					//ミサイルがセットされていなければタイマーを進める
		m_leftmissilegaugelevel = min(1.0f, m_leftbullettime / BULLETSPAN);
	}
	if (m_leftbullettime >= BULLETSPAN && m_leftbullet == nullptr)
	{
		m_leftbullet = new bullet(0, "bullet");				//左のミサイルをセット
		m_leftbullet->WitchBullet(isPlayer);
		m_leftbullet->SetTarget(LockOnEnemy);
		m_leftbullet->SetLeft_or_Rite(Left);
		m_leftbullettime = 0.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA))
	{
		//ミサイルがセットされていれば撃つ
		if (m_ritebullet != nullptr)
		{
			if (m_class_of_newgo != nullptr)
			{
				if (m_class_of_newgo->GetFireSE()->IsPlaying())
				{
					m_class_of_newgo->GetFireSE()->Stop();
				}
				m_class_of_newgo->GetFireSE()->Play(false);
			}
			m_ritebullet->SetBulletParam();
			m_ritebullet = nullptr;
			m_ritemissilegaugelevel = 0.0f;
		}
		else if (m_leftbullet != nullptr)
		{
			if (m_class_of_newgo != nullptr)
			{
				if (m_class_of_newgo->GetFireSE()->IsPlaying())
				{
					m_class_of_newgo->GetFireSE()->Stop();
				}
				m_class_of_newgo->GetFireSE()->Play(false);
			}
			m_leftbullet->SetBulletParam();
			m_leftbullet = nullptr;
			m_leftmissilegaugelevel = 0.0f;
		}
	}
}

void Player::SpriteManager()
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
		m_aimsprite.Update(
			SCpos,
			CQuaternion::Identity(),
			CVector3::One()*0.08f
		);
	}
	/*ロックオンスプライトのポジションを計算*/
	{
		CMatrix wvp;
		wvp.MakeTranslation(m_lockonenemypos);
		wvp.Mul(wvp, g_camera3D.GetViewMatrix());
		wvp.Mul(wvp, g_camera3D.GetProjectionMatrix());
		CVector3 LOEP = { wvp.m[3][0], wvp.m[3][1],wvp.m[3][2] };
		LOEP = LOEP / wvp.m[3][3];
		LOEP.x *= FRAME_BUFFER_W / 2.0f;
		LOEP.y *= FRAME_BUFFER_H / 2.0f;
		LOEP.z = 0.0f;
		m_lockonsprite.Update(
			LOEP,
			CQuaternion::Identity(),
			CVector3::One()*0.2f
		);
	}
}

void Player::Update()
{
	/*リファクタリング予定*/
	if (m_class_of_newgo->GetWaveCounter() == 5)
	{
		m_playerstate = Boss;
	}
	switch (m_playerstate)
	{
	case Nomal:					//通常のプレイヤーの動き
	{
		PlayerMove();
		break;
	}
	case Return:				//エリア外から帰還する際ののプレイヤーの動き
	{
		PlayerReturn();
		break;
	}
	case Boss:
	{
		if (!m_bossfightinitflag)
		{
			BossFightInit();
		}
		BossFightMove();
		break;
	}
	}
	Vector();

	if (CVector3(m_position - CVector3::Zero()).Length() > 100000.0f)
	{
		m_playerstate = Return;
	}
	else
	{
		m_playerstate = Nomal;
	}
	m_position = m_characon.Execute(deltaTime, movespeed, m_rotation);
	BulletManager();


	if (m_playerparam.HP <= 0)
	{
		m_class_of_newgo->GetEffect()->Play(m_position, CVector3::One()*100.0f);
		game_obj->DeleteGO(this);
	}
	m_playerparam.Time = max(0.0f, m_playerparam.Time - (1.0f*deltaTime));


	//ワールド行列の更新。
	m_skinmodel.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_skinmodel);

	m_leftrechargeHUD.Update(MISSILE_RECHARGE_L_GAGE_POS, CQuaternion::Identity(), m_leftmissilegaugelevel);
	m_riterechargeHUD.Update(MISSILE_RECHARGE_R_GAGE_POS, CQuaternion::Identity(), m_ritemissilegaugelevel);
	float HPGauge = m_playerparam.HP / HPMAX;
	m_hpHUD.Update(HP_GAUGE_POS, CQuaternion::Identity(), HPGauge);
	m_class_of_newgo->GetResult()->SetRemHP(m_playerparam.HP);
	SpriteManager();
}
/*
通常の描画
*/
void Player::Draw()
{
	//プレイヤーの描画
	m_skinmodel.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}

void Player::EffectDraw()
{
	for (const auto& effct : m_spriteeffectlist)
	{
		CVector3 pos = m_rite * effct->m_toengin.x + m_up * effct->m_toengin.y + m_forward * effct->m_toengin.z;
		effct->m_spriteeffect.Update(m_position + pos);
		effct->m_spriteeffect.Draw();
	}
}



void Player::PostDraw()
{
	//スプライトの描画
	m_aimsprite.Draw(
		*g_graphicsEngine->GetD3DDeviceContext()
	);
	if (m_lockonflag)
	{
		m_lockonsprite.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}

}

void Player::UIDraw()
{
	m_leftrechargeHUD.Draw();
	m_riterechargeHUD.Draw();
	m_hpHUD.Draw();
}

void Player::OnDestroy()
{
	for (const auto& effct : m_spriteeffectlist)
	{
		delete effct;
	}
	m_spriteeffectlist.clear();
	if (m_ritebullet != nullptr)
	{
		game_obj->DeleteGO(m_ritebullet);
	}
	if (m_leftbullet != nullptr)
	{
		game_obj->DeleteGO(m_leftbullet);
	}
}
