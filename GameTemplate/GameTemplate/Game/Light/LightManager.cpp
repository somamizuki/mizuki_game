#include "stdafx.h"


LightManager::LightManager()
{
}


LightManager::~LightManager()
{
	for (auto& light_it : anyLight)
	{
		delete light_it;
	}
}

void LightManager::SetLightParam(ligParam& ligparam)
{
	ConstantBuffer m_cb;
	m_cb.Create(&ligparam, sizeof(ligParam));
	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
	d3dDC->VSSetConstantBuffers(10, 1, &m_cb.GetBody());
	d3dDC->PSSetConstantBuffers(10, 1, &m_cb.GetBody());
}

void LightManager::LightExecute()
{
	for (auto& light_it : anyLight)
	{
		if (!light_it->GetisInit())
		{
			if (light_it->InitLightSB())
			{
				light_it->SetisInit(true);
			}
		}
		light_it->UpdateSubresource();
	}

	for (auto& light_it : anyLight)
	{
		if (light_it->GetisInit())
		{
			light_it->SendStructuredBuffer();
		}
	}



}