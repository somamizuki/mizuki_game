#include "stdafx.h"
#include "SpriteEffect.h"


SpriteEffect::SpriteEffect()
{
}


SpriteEffect::~SpriteEffect()
{
	for (const auto& EffectSprite : EffectSpriteList)
	{
		delete EffectSprite;
	}
}

void SpriteEffect::Init(ID3D11ShaderResourceView* SRV, float time, int span)
{
	m_SRV = SRV;
	eraseTime = time;
	m_Span = span;
	changesize = eraseTime / deltaTime;
}

void SpriteEffect::Update(CVector3& position)
{
	if (m_frame >= m_Span)
	{
		GenerateSprite(position);
		m_frame = 0;
	}
	m_frame++;
	std::list<SEffectSprite*> dethlist;
	for (const auto& EffectSprite : EffectSpriteList)
	{
		if (EffectSprite->time >= eraseTime)
		{
			dethlist.push_back(EffectSprite);
		}
		else
		{
			EffectSprite->time += 1.0f*deltaTime;
			CVector3 toCameraVec = g_camera3D.GetPosition() - EffectSprite->m_position;
			toCameraVec.Normalize();
			CVector3 spritefront = CVector3::AxisZ()*-1.0f;
			float angle = CMath::RadToDeg(Acos(spritefront.Dot(toCameraVec)));
			CVector3 Axis;
			Axis.Cross(toCameraVec, spritefront);
			Axis.Normalize();
			CQuaternion qRot = CQuaternion::Identity();

			qRot.SetRotationDeg(Axis, -angle);
			CMatrix rotM;
			rotM.MakeRotationFromQuaternion(qRot);
			EffectSprite->m_forward = CVector3(rotM.m[2][0], rotM.m[2][1], rotM.m[2][2]);
			EffectSprite->m_rite = CVector3(rotM.m[1][0], rotM.m[1][1], rotM.m[1][2]);
			EffectSprite->m_up = CVector3(rotM.m[0][0], rotM.m[0][1], rotM.m[0][2]);
			EffectSprite->m_forward.Normalize();
			EffectSprite->m_rite.Normalize();
			EffectSprite->m_up.Normalize();

			EffectSprite->m_sprite.Update(EffectSprite->m_position, qRot, CVector3::One()*EffectSprite->size);


			EffectSprite->size = max(0.0001f, EffectSprite->size - (EffectSprite->size / changesize));
			EffectSprite->m_sprite.SetViewProj(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
		}
	}

	for (const auto& dethSES : dethlist)
	{
		for (const auto& EffectSprite : EffectSpriteList)
		{
			if (EffectSprite == dethSES)
			{
				delete EffectSprite;
				EffectSpriteList.erase(std::remove(EffectSpriteList.begin(), EffectSpriteList.end(), EffectSprite), EffectSpriteList.end());
				break;
			}
		}
	}



	m_time = 1.0f*deltaTime;
}

void SpriteEffect::Draw()
{
	for (auto& EffectSprite : EffectSpriteList)
	{
		EffectSprite->m_sprite.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
}

void SpriteEffect::GenerateSprite(CVector3 position)
{
	SEffectSprite* effectsprite = new SEffectSprite;
	m_SRV->AddRef();
	effectsprite->m_sprite.Init(m_SRV, 512.0f, 512.0f);
	effectsprite->m_position = position;
	effectsprite->Initflag = true;
	EffectSpriteList.push_back(effectsprite);
}
