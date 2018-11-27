#include "stdafx.h"
#include "CDirectionLight.h"


CDirectionLight::CDirectionLight()
{
	this->SetLightType(LightType(Direction));
	Light_obj->PushLight(this);
}


CDirectionLight::~CDirectionLight()
{
	Light_obj->DeleteLight(this);
}

bool CDirectionLight::InitLightSB()
{
	D3D11_BUFFER_DESC lightDesc;
	ZeroMemory(&lightDesc, sizeof(lightDesc));
	lightDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	lightDesc.ByteWidth = sizeof(SDirectionLight) * DirectionMaxSum;
	lightDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	lightDesc.StructureByteStride = sizeof(SDirectionLight);

	m_sb.Create(NULL, lightDesc);
	return true;
}

void CDirectionLight::UpdateSubresource()
{
	/*if (!creatf)
	{
		D3D11_BUFFER_DESC lightDesc;
		ZeroMemory(&lightDesc, sizeof(lightDesc));
		lightDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		lightDesc.ByteWidth = sizeof(SDirectionLight) * DirectionMaxSum;
		lightDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		lightDesc.StructureByteStride = sizeof(SDirectionLight);

		m_sb.Create(&ligstruct, lightDesc);
		creatf = true;
	}*/
	

	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();

	d3dDC->UpdateSubresource(m_sb.GetBody(), 0, nullptr, &ligstruct, 0, 0);
}

void CDirectionLight::SendStructuredBuffer()
{
	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
	SendConstantBuffer();
	d3dDC->VSSetShaderResources(100, 1, &m_sb.GetSRV().GetBody());
	d3dDC->PSSetShaderResources(100, 1, &m_sb.GetSRV().GetBody());
}
void CDirectionLight::SendConstantBuffer()
{
	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
	m_cb.Create(&DirSum, sizeof(DirSum));
	d3dDC->VSSetConstantBuffers(1, 1, &m_cb.GetBody());
	d3dDC->PSSetConstantBuffers(1, 1, &m_cb.GetBody());

}