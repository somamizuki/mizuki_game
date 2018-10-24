#include "stdafx.h"
#include "LightBase.h"

LightBase::LightBase()
{
}

LightBase::~LightBase()
{
}

void LightBase::InitDirectionLightSB(void* anylight)
{
	SDirectionLight direction;
	direction.color = { 0.0f,0.0f,0.0f,0.0f };
	direction.Direction = { 0.0f,0.0f,0.0f,0.0f };

	D3D11_BUFFER_DESC lightDesc;
	ZeroMemory(&lightDesc, sizeof(lightDesc));
	lightDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	lightDesc.ByteWidth = sizeof(SDirectionLight) * 8;
	lightDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	lightDesc.StructureByteStride = sizeof(SDirectionLight);

	directionlightSB.Create(anylight, lightDesc);
}

void LightBase::InitPointLightSB(void* anylight)
{
	SPointLight pointLig;
	pointLig.color = { 0.0f,0.0f,0.0f,0.0f };
	pointLig.position = { 0.0f,0.0f,0.0f,0.0f };
	pointLig.range = 0.0f;

	D3D11_BUFFER_DESC lightDesc;
	ZeroMemory(&lightDesc, sizeof(lightDesc));
	lightDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	lightDesc.ByteWidth = sizeof(SPointLight) * 1024;
	lightDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	lightDesc.StructureByteStride = sizeof(SPointLight);

	pointlightSB.Create(anylight, lightDesc);
}

void LightBase::InitSpotLightSB(void* anylight)
{
	SSpotLight spot;
	spot.color = { 0.0f,0.0f,0.0f,0.0f };
	spot.Direction = { 0.0f,0.0f,0.0f,0.0f };
	spot.position = { 0.0f,0.0f,0.0f,0.0f };
	spot.SpotAngle = 0.0f;
	spot.range = 0.0f;

	D3D11_BUFFER_DESC lightDesc;
	ZeroMemory(&lightDesc, sizeof(lightDesc));
	lightDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	lightDesc.ByteWidth = sizeof(SSpotLight) * 1024;
	lightDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	lightDesc.StructureByteStride = sizeof(SSpotLight);

	spotlightSB.Create(anylight, lightDesc);
}







void LightBase::InitLight(void* anylight,LightType lighttype,int sum)
{

	
	InitDirectionLightSB(anylight);
	InitPointLightSB(anylight);
	InitSpotLightSB(anylight);
	Ligtype = lighttype;

	switch (Ligtype) {
	case Direction: {
		lightsum = sum / sizeof(SDirectionLight);
		break;
	}
	case Point: {
		lightsum = sum / sizeof(SPointLight);
		break;
	}
	case Spot: {
		lightsum = sum / sizeof(SSpotLight);
		break;
	}
	}
}
void LightBase::LightUpdateSubresource(const void* AnyLight)
{
	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
	switch (Ligtype)
	{
	case Direction:
	{
		d3dDC->UpdateSubresource(directionlightSB.GetBody(), 0, nullptr, AnyLight, 0, 0);
		thislightSB = &directionlightSB;
		break;
	}
	case Point:
	{
		d3dDC->UpdateSubresource(pointlightSB.GetBody(), 0, nullptr, AnyLight, 0, 0);
		thislightSB = &pointlightSB;
		break;
	}
	case Spot:
	{
		d3dDC->UpdateSubresource(spotlightSB.GetBody(), 0, nullptr, AnyLight, 0, 0);
		thislightSB = &spotlightSB;
		break;
	}
	}

}

void LightBase::SendConstantBuffer()
{
	ID3D11DeviceContext* d3dDC = g_graphicsEngine->GetD3DDeviceContext();
	
	//ConstantBuffer m_cb2, m_cb3;
	//nolig no;
	//no.zero = 0;

	///*
	//使わないライトの定数バッファも初期化。
	//*/
	//switch (Ligtype)
	//{
	//case Direction: {
	//	thislightSB = &directionlightSB;

	//	d3dDC->VSSetShaderResources(Point, 1, &pointlightSB.GetSRV().GetBody());
	//	d3dDC->PSSetShaderResources(Point, 1, &pointlightSB.GetSRV().GetBody());
	//	d3dDC->VSSetShaderResources(Spot, 1, &spotlightSB.GetSRV().GetBody());
	//	d3dDC->PSSetShaderResources(Spot, 1, &spotlightSB.GetSRV().GetBody());

	//	m_cb2.Create(&no, sizeof(nolig));
	//	d3dDC->VSSetConstantBuffers(Point, 1, &m_cb2.GetBody());
	//	d3dDC->PSSetConstantBuffers(Point, 1, &m_cb2.GetBody());
	//	m_cb3.Create(&no, sizeof(nolig));
	//	d3dDC->VSSetConstantBuffers(Spot, 1, &m_cb3.GetBody());
	//	d3dDC->PSSetConstantBuffers(Spot, 1, &m_cb3.GetBody());
	//	break;
	//}
	//case Point: {
	//	thislightSB = &pointlightSB;

	//	d3dDC->VSSetShaderResources(Direction, 1, &directionlightSB.GetSRV().GetBody());
	//	d3dDC->PSSetShaderResources(Direction, 1, &directionlightSB.GetSRV().GetBody());
	//	d3dDC->VSSetShaderResources(Spot, 1, &spotlightSB.GetSRV().GetBody());
	//	d3dDC->PSSetShaderResources(Spot, 1, &spotlightSB.GetSRV().GetBody());

	//	m_cb2.Create(&no, sizeof(nolig));
	//	d3dDC->VSSetConstantBuffers(Direction, 1, &m_cb2.GetBody());
	//	d3dDC->PSSetConstantBuffers(Direction, 1, &m_cb2.GetBody());
	//	m_cb3.Create(&no, sizeof(nolig));
	//	d3dDC->VSSetConstantBuffers(Spot, 1, &m_cb3.GetBody());
	//	d3dDC->PSSetConstantBuffers(Spot, 1, &m_cb3.GetBody());
	//	break;
	//}
	//case Spot: {
	//	thislightSB = &spotlightSB;

	//	d3dDC->VSSetShaderResources(Direction, 1, &directionlightSB.GetSRV().GetBody());
	//	d3dDC->PSSetShaderResources(Direction, 1, &directionlightSB.GetSRV().GetBody());
	//	d3dDC->VSSetShaderResources(Point, 1, &pointlightSB.GetSRV().GetBody());
	//	d3dDC->PSSetShaderResources(Point, 1, &pointlightSB.GetSRV().GetBody());

	//	m_cb2.Create(&no, sizeof(nolig));
	//	d3dDC->VSSetConstantBuffers(Direction, 1, &m_cb2.GetBody());
	//	d3dDC->PSSetConstantBuffers(Direction, 1, &m_cb2.GetBody());
	//	m_cb3.Create(&no, sizeof(nolig));
	//	d3dDC->VSSetConstantBuffers(Point, 1, &m_cb3.GetBody());
	//	d3dDC->PSSetConstantBuffers(Point, 1, &m_cb3.GetBody());
	//	break;
	//}
	//default:throw;
	//}
	d3dDC->VSSetShaderResources(Ligtype+100, 1, &thislightSB->GetSRV().GetBody());
	d3dDC->PSSetShaderResources(Ligtype+100, 1, &thislightSB->GetSRV().GetBody());

	m_cb.Create(&lightsum, sizeof(lightsum));
	m_ligparamCB.Create(&ligP, sizeof(ligP));
	d3dDC->VSSetConstantBuffers(Ligtype, 1, &m_cb.GetBody());
	d3dDC->PSSetConstantBuffers(Ligtype, 1, &m_cb.GetBody());
	if (specF==true)
	{
		d3dDC->VSSetConstantBuffers(10, 1, &m_ligparamCB.GetBody());
		d3dDC->PSSetConstantBuffers(10, 1, &m_ligparamCB.GetBody());
	}

}