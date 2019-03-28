#pragma once
#include "RenderTarget.h"
class SkinModel;
class ShadowMap
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ShadowMap();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ShadowMap();
	/// <summary>
	/// ライトのビューマトリクス
	/// </summary>
	/// <returns>CMatrix</returns>
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}
	/// <summary>
	/// ライトのビューマトリクス
	/// </summary>
	/// <returns>CMatrix</returns>
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}
	/// <summary>
	/// ライトカメラの方向を計算する関数
	/// </summary>
	/// <param name="lightCameraPos">ライトカメラのポジション(CVector3)</param>
	/// <param name="lightCameraTarget">ライトカメラのターゲット(CVector3)</param>
	void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	/// <summary>
	/// ライトカメラの方向からビュー行列とプロジェクション行列を更新する関数
	/// </summary>
	/// <param name="lightCameraPos">ライトカメラのポジション(CVector3)</param>
	/// <param name="lightDir">ライトカメラの方向(CVector3)</param>
	void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);
	/// <summary>
	/// シャドウキャスターに登録されたモデルをシャドウマップ用のレンダリングターゲットに描画する関数
	/// </summary>
	void RenderToShadowMap();
	/// <summary>
	/// シャドウキャスターを登録する関数
	/// </summary>
	/// <param name="shadowCaster"></param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
	/// <summary>
	/// シャドウマップの描画関数
	/// </summary>
	void ShadowMapDraw();
	/// <summary>
	/// シャドウマップSRVのゲッター
	/// </summary>
	/// <returns>ID3D11ShaderResourceView*</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3					m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点。
	CVector3					m_lightCameraTarget = CVector3::Zero();		//ライトカメラの注視点。
	CMatrix						m_lightViewMatrix = CMatrix::Identity();	//ライトビュー行列。
	CMatrix						m_lightProjMatrix = CMatrix::Identity();	//ライトプロジェクション行列。
	RenderTarget				m_shadowMapRT;								//シャドウマップを描画するレンダリングターゲット。
	std::vector< SkinModel*>	m_shadowCasters;							//シャドウキャスターの配列。
};

