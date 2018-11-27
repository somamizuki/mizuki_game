#include "stdafx.h"
#include "CPointLight.h"


CPointLight::CPointLight()
{
	this->SetLightType(LightType(Point));
	Light_obj->PushLight(this);
}


CPointLight::~CPointLight()
{
	Light_obj->DeleteLight(this);
}

bool CPointLight::InitLightSB()
{
	D3D11_BUFFER_DESC lightDesc;
	ZeroMemory(&lightDesc, sizeof(lightDesc));
	lightDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	lightDesc.ByteWidth = sizeof(SPointLight) * PointMaxSum;
	lightDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	lightDesc.StructureByteStride = sizeof(SPointLight);

	m_sb.Create(NULL, lightDesc);
	return true;
}

void CPointLight::UpdateSubresource()
{

	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();

	d3dDC->UpdateSubresource(m_sb.GetBody(), 0, nullptr, &ligstruct, 0, 0);
}

void CPointLight::SendStructuredBuffer()
{
	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
	SendConstantBuffer();
	d3dDC->VSSetShaderResources(101, 1, &m_sb.GetSRV().GetBody());
	d3dDC->PSSetShaderResources(101, 1, &m_sb.GetSRV().GetBody());
}
void CPointLight::SendConstantBuffer()
{
	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
	m_cb.Create(&PointSum, sizeof(PointSum));
	d3dDC->VSSetConstantBuffers(2, 1, &m_cb.GetBody());
	d3dDC->PSSetConstantBuffers(2, 1, &m_cb.GetBody());

}