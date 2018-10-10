#include "stdafx.h"
#include "LightBase.h"

namespace Light{
	LightBase::LightBase()
	{
	}

	LightBase::~LightBase()
	{
	}

	void LightBase::InitLight(SDirectionLight* dirLight) {
		SDir = dirLight;
		m_cb.Create(&dirLight, sizeof(dirLight));
		Ligtype = Direction;
	}
	void LightBase::InitLight(SPointLight* pointLight) {
		m_cb.Create(&pointLight, sizeof(pointLight));
		Ligtype = Point;
	}
	void LightBase::InitLight(SSpotLight* spotLight) {
		m_cb.Create(&spotLight, sizeof(spotLight));
		Ligtype = Spot;
	}
	void LightBase::LightUpdateSubresource()
	{
		switch (Ligtype)
		{
		Direction: {
			ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
			d3dDC->UpdateSubresource(m_cb.GetBody(), 0, nullptr, &SDir, 0, 0);
			}
		}
		
	}
}

