#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	switch (m)
	{
	case Diffuse: {
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		break;
	}
	case LightOn: {
		m_psShader.Load("Assets/shader/model.fx", "PS2Main", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		/*ID3D11ShaderResourceView* srvArray[] = {
			g_graphicsEngine->GetShadowMap()->GetShadowMapSRV()
		};*/
		ID3D11ShaderResourceView* srvArray = g_graphicsEngine->GetShadowMap()->GetShadowMapSRV();
		deviceContext->PSSetShaderResources(2, 1, &srvArray);
		break;
	}
	case PointLight: {
		m_psShader.Load("Assets/shader/model.fx", "PS3Main", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		break;
	}
	case CubeMap: {
		m_psShader.Load("Assets/shader/model.fx", "PSCubeMain", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		break;
	}
	case Shadow: {
		m_psShader.Load("Assets/shader/model.fx", "PSShadowMapMain", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		m_vsShader.Load("Assets/shader/model.fx", "VSShadowMapMain", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		break;
	}
	default:

		break;
	}
	deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);

}