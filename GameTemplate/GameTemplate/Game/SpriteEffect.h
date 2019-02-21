#pragma once
class SpriteEffect
{
public:
	SpriteEffect();
	~SpriteEffect();
	void Init(ID3D11ShaderResourceView* SRV, float time, int span);
	void Update(CVector3& position);
	void Draw();
private:
	void GenerateSprite(CVector3 position);
	float Acos(float dotresult)
	{
		float angle = acosf(min(1.0f, max(-1.0f, dotresult)));
		return angle;
	}

private:
	struct SEffectSprite{
		sprite m_sprite;
		CVector3 m_position = CVector3::Zero();
		CVector3 m_forward = CVector3::AxisZ()*-1.0f;
		CVector3 m_rite = CVector3::AxisX()*-1.0f;
		CVector3 m_up = CVector3::AxisY();
		float size = 0.2f;
		float time = 0.0f;
		bool dethflag = false;
		bool Initflag = false;
	};
	
	std::list<SEffectSprite*> EffectSpriteList;
	ID3D11ShaderResourceView* m_SRV;
	float m_time = 0.0f;
	float changesize = 0.0f;
	float eraseTime;
	int m_frame = 0;
	int m_Span;
};

