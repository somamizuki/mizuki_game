#pragma once

namespace Light {
	struct SDirectionLight {
		CVector4 color;
		CVector4 Direction;
		CVector4 position;
	};
}

using namespace Light;

class DirectionLight
{
public:
	DirectionLight();
	~DirectionLight();
	void InitDirectionLight();
	const SDirectionLight Getm_directionLight() const
	{
		return m_directionLight;
	}
	void Setm_directionLight(SDirectionLight* SD)
	{
		m_directionLight = *SD;
	}
	
	ConstantBuffer* Get_constantBuffer()
	{
		return &m_constantBuffer;
	}

private:
	ConstantBuffer m_constantBuffer;
	SDirectionLight m_directionLight;
};

