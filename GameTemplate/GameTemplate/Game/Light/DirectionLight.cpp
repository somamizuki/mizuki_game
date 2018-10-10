#include "stdafx.h"
#include "DirectionLight.h"

	DirectionLight::DirectionLight()
	{
	}


	DirectionLight::~DirectionLight()
	{
	}

	void DirectionLight::InitDirectionLight()
	{
		m_constantBuffer.Create(&m_directionLight, sizeof(SDirectionLight));
	}
