#include "stdafx.h"
#include "BossEnemy.h"



BossEnemy::BossEnemy(int No, const char* obj_name) : GameObject(No, obj_name)
{
}

BossEnemy::~BossEnemy()
{
}

bool BossEnemy::Start()
{
	m_player = game_obj->FindGO<Player>("player");
	m_player->AddMyPointer<Player, BossEnemy>(&m_player, this);
	m_skinmodel.Init(L"Assets/modelData/BossEnemy2.cmo");
	m_skinmodel.SetNormalMap(L"Resource/sprite/SGNormal.dds");
	m_skinmodel.SetShadowReciever(true);
	m_animationClip[0].Load(L"Assets/animData/Punching.tka");
	m_animationClip[0].SetLoopFlag(true);
	m_animation.Init(m_skinmodel, m_animationClip, 1);

	if (m_player->Getup().Dot(CVector3::AxisY()) < 0.9999999999f)
	{
		float dotresult = m_player->Getup().Dot(CVector3::AxisY());
		float angle = Acos(dotresult);
		CVector3 axis = CVector3::Zero();
		axis.Cross(m_player->Getup(), CVector3::AxisY());
		axis.Normalize();
		m_rotation.SetRotation(axis, -angle);
	}
	Vector();
	m_animation.Play(0, 0.3f);
	m_animation.Update(deltaTime);
	CMatrix boneWM = m_skinmodel.FindBone(L"mixamorig:RightHandMiddle1")->GetWorldMatrix();
	olsbonepos = { boneWM.m[3][0],boneWM.m[3][1], boneWM.m[3][2] };
	return true;
}

void BossEnemy::Update()
{
	rotmanager();
	if (!m_animation.IsPlaying())
	{
		m_animation.Play(0, 0.3f);
		m_animation.Update(deltaTime);
	}

	m_animation.Update(deltaTime);
	m_skinmodel.UpdateWorldMatrix(m_position, m_rotation, m_scale*50.0f);

	CMatrix boneWM = m_skinmodel.FindBone(L"mixamorig:RightHandMiddle1")->GetWorldMatrix();
	CVector3 bonepos = { boneWM.m[3][0],boneWM.m[3][1], boneWM.m[3][2] };
	CollisionDetection collisiondetection;
	if (collisiondetection.IsHIT(olsbonepos, bonepos, 100.0f) && m_player != nullptr)
	{
		m_player->SetHP(10);
	}
	olsbonepos = bonepos;
}

void BossEnemy::Draw()
{
	m_skinmodel.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void BossEnemy::Vector()
{
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_right = { mRot.m[0][0],mRot.m[0][1],mRot.m[0][2] };
	m_up = { mRot.m[1][0],mRot.m[1][1],mRot.m[1][2] };
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_right.Normalize();
	m_up.Normalize();
	m_forward.Normalize();
}

void BossEnemy::rotmanager()
{
	if (m_player != nullptr)m_playerpos = m_player->Getpos();
	CVector3 toPlayer = m_playerpos - m_position;
	float flen = m_forward.Dot(toPlayer);
	float rlen = m_right.Dot(toPlayer);
	toPlayer = m_forward * flen + m_right * rlen;
	//toPlayer = toPlayer + (m_up*-uplen);
	toPlayer.Normalize();
	float dotresult = toPlayer.Dot(m_forward);
	float angle = Acos(dotresult);
	CVector3 axis;
	axis.Cross(m_forward, toPlayer);
	axis.Normalize();
	if (m_up.Dot(axis) < -0.9f)angle *= -1.0f;
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotation(CVector3::AxisY(), angle);
	m_rotation.Multiply(rot);

	Vector();
}
