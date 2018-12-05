#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	switch (m)
	{
	case 1: {
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		break;
	}
	case 2: {
		m_psShader.Load("Assets/shader/model.fx", "PS2Main", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		break;
	}
	case 3: {
		m_psShader.Load("Assets/shader/model.fx", "PS3Main", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		break;
	}
	case 4: {
		m_psShader.Load("Assets/shader/model.fx", "PSCubeMain", Shader::EnType::PS);
		m_pPSShader = &m_psShader;
		break;
	}
	default:

		break;
	}
	deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);

}