#include "stdafx.h"
#include "bullet.h"
#include"Player.h"


CVector3 bulletmodellocal = CVector3::AxisZ();		//モデル座標系の前に当たるワールドの軸Zを代入
bullet::bullet(int No, const char* obj_name) : GameObject(No, obj_name)
{
}


bullet::~bullet()
{

}

bool bullet::Start()
{

	m_skinmodel.Init(L"Assets/modelData/missile.cmo");					//玉のモデルイニット
	m_skinmodel.SetNormalMap(L"Resource/sprite/7_normal.dds");				//ノーマルマップをセット
	m_player = game_obj->FindGO<Player>("player");					//プレイヤーの検索
	m_player->AddMyPointer<Player, bullet>(&m_player, this);
	m_class_of_newgo = game_obj->FindGO<Class_of_NewGO>("newObject");			//いろんなクラスをnewするクラスを検索
	m_class_of_newgo->AddMyPointer<Class_of_NewGO, bullet>(&m_class_of_newgo, this);
	switch (m_witchbullet)
	{
	case isPlayer: {
		m_movedirection = m_player->GetForward();								//玉のディレクションにプレイヤーのフォワードを代入

		switch (m_left_or_rite)		//左右どちらかにミサイルをつける
		{
		case Left: {
			m_position = m_player->GetPosition() + (m_player->GetRite()*-80.0f) + (m_player->GetUp() *-20.0f);
			m_rotation = m_player->GetRotation();
			break;
		}
		case Rite: {
			m_position = m_player->GetPosition() + (m_player->GetRite()*80.0f) + (m_player->GetUp() *-20.0f);
			m_rotation = m_player->GetRotation();
			break;
		}
		default:
			break;
		}
		break;
	}
	case isEnemy: {
		switch (m_left_or_rite)		//左右どちらかにミサイルをつける
		{
		case Left: {
			m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*-80.0f) + (m_enemy->GetUp() *-20.0f);
			m_rotation = m_enemy->GetRotation();
			break;
		}
		case Rite: {
			m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*80.0f) + (m_enemy->GetUp() *-20.0f);
			m_rotation = m_enemy->GetRotation();
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	m_srv.CreateFromDDSTextureFromFile(L"Resource/sprite/fog.dds");
	m_spriteeffect.Init(m_srv.GetBody(), 0.15f, 0);
	return true;
}

void bullet::UpdateVector()
{
	/*クオータニオンからモデルの軸を更新*/
	CMatrix RotM;
	RotM.MakeRotationFromQuaternion(m_rotation);
	m_rite = { RotM.m[0][0] , RotM.m[0][1] ,RotM.m[0][2] };
	m_up = { RotM.m[1][0] , RotM.m[1][1] ,RotM.m[1][2] };
	m_forward = { RotM.m[2][0] , RotM.m[2][1] ,RotM.m[2][2] };
	m_rite.Normalize();
	m_up.Normalize();
	m_forward.Normalize();
}

void bullet::BulletHoming(CVector3& target)
{
	CVector3 BtoT;					//弾からターゲットに向かうベクトル
	BtoT = target - m_position;
	BtoT.Normalize();
	m_movedirection = m_forward * 10.0f + BtoT;		//弾の進行方向を設定	30は調整
	m_movedirection.Normalize();					//正規化


	if (abs(bulletmodellocal.Dot(m_movedirection)) <= 0.9999999999999f)//同軸の外積をとらないように除外
	{
		CVector3 forwardModelLocal = bulletmodellocal;
		float dotresult = forwardModelLocal.Dot(m_movedirection);	//無回転状態のモデルの前方向と、弾の進行方向との内積
		CVector3 Axis;
		Axis.Cross(m_movedirection, forwardModelLocal);				//外積で回転の軸を作る
		Axis.Normalize();									//正規化
		m_rotation.SetRotation(Axis, -Acos(dotresult));		//作成した軸周りに回転

		UpdateVector();										//軸の更新
	}
	m_position += m_forward * m_speed * deltaTime;
}

void bullet::BulletFire()
{
	switch (m_witchbullet)
	{
	case isPlayer: {
		if (m_lockonenemy != nullptr)
		{
			CVector3 target = m_lockonenemy->GetPosition();
			CVector3 toTarget = target - m_position;
			toTarget.Normalize();
			m_ishoming = m_forward.Dot(toTarget) > 0.0f &&CVector3(m_player->GetPosition() - m_position).Length() > 1000.0f;

			if (m_ishoming)
			{
				BulletHoming(target);
			}
			else
			{
				m_position += m_forward * m_speed * deltaTime;
			}

			toTarget = m_lockonenemy->GetPosition() - m_position;


			if (toTarget.Length() < 300.0f)
			{
				game_obj->DeleteGO(m_lockonenemy);
				if (m_class_of_newgo != nullptr)
				{
					if (m_class_of_newgo->GetHitSE()->IsPlaying())
					{
						m_class_of_newgo->GetHitSE()->Stop();
					}
					m_class_of_newgo->GetHitSE()->Play(false);
				}
				game_obj->DeleteGO(this);
			}
		}
		else
		{
			m_position += m_forward * m_speed * deltaTime;
		}

		break;
	}
	case isEnemy: {
		CVector3 target = m_player->GetPosition();
		CVector3 toTarget = target - m_position;
		toTarget.Normalize();
		m_ishoming = m_forward.Dot(toTarget) > 0.0f &&CVector3(m_enemy->GetPosition() - m_position).Length() > 1000.0f;
		if (m_ishoming)
		{
			BulletHoming(target);
		}
		else
		{
			m_position += m_forward * m_speed * deltaTime;
		}

		if (m_player != nullptr && !this->GetDeath_f())
		{
			CVector3 toPlayer = m_player->GetPosition() - m_position;
			bool HitPlayer = toPlayer.Length() < 200.0f;
			if (HitPlayer)
			{
				m_player->SetHP(1);
				if (m_class_of_newgo != nullptr)
				{
					if (m_class_of_newgo->GetHitSE()->IsPlaying())
					{
						m_class_of_newgo->GetHitSE()->Stop();
					}
					m_class_of_newgo->GetHitSE()->Play(false);
				}
				game_obj->DeleteGO(this);
			}
		}

		break;
	}
	default:
		break;
	}
}

void bullet::Update()
{
	if (m_player != nullptr)
	{
		m_playerposition = m_player->GetPosition();
	}

	UpdateVector();
	if (m_fireflag)
	{
		if (m_player != nullptr)
		{
			BulletFire();
		}
		else
		{
			m_position += m_forward * m_speed * deltaTime;
		}


		if (m_speed < bulletspeed)
		{
			m_speed += 100.0f;
		}
		m_time += 1.0f*deltaTime;

		if (m_time >= 10.0f)
		{
			game_obj->DeleteGO(this);
		}

	}
	else
	{
		switch (m_witchbullet)
		{
		case isPlayer: {
			if (m_player == nullptr)
			{
				game_obj->DeleteGO(this);
			}
			else
			{
				switch (m_left_or_rite)		//左右どちらかにミサイルをつける
				{
				case Left: {
					m_position = m_player->GetPosition() + (m_player->GetRite()*-80.0f) + (m_player->GetUp() *-20.0f);
					m_rotation = m_player->GetRotation();
					break;
				}
				case Rite: {
					m_position = m_player->GetPosition() + (m_player->GetRite()*80.0f) + (m_player->GetUp() *-20.0f);
					m_rotation = m_player->GetRotation();
					break;
				}
				default:
					break;
				}
			}
			break;
		}
		case isEnemy: {
			if (m_enemy != nullptr)
			{
				switch (m_left_or_rite)		//左右どちらかにミサイルをつける
				{
				case Left: {
					m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*-80.0f) + (m_enemy->GetUp() *-20.0f);
					m_rotation = m_enemy->GetRotation();
					break;
				}
				case Rite: {
					m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*80.0f) + (m_enemy->GetUp() *-20.0f);
					m_rotation = m_enemy->GetRotation();
					break;
				}
				default:
					break;
				}
			}


			break;
		}
		default:
			break;
		}
	}
	if (m_class_of_newgo == nullptr)
	{
		game_obj->DeleteGO(this);
	}

	m_skinmodel.UpdateWorldMatrix(m_position, m_rotation, CVector3::One()*2.0f);		//ワールドマトリクスの更新
}

void bullet::Draw()
{
	m_skinmodel.Draw(																				//弾の描画
		LightOn,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}

void bullet::EffectDraw()
{
	if (m_fireflag)
	{
		m_spriteeffect.Update(m_position + m_forward * -170.0f);
		m_spriteeffect.Draw();
	}

}

void bullet::OnDestroy()
{
}
