#pragma once
#include"GaussianBlur.h"
#include"Shader.h"
class Bloom
{
public:
	Bloom();
	~Bloom();
	void Init();
	void Update();


private:
	ID3D11SamplerState* m_samplerState = nullptr;			//サンプラステート。
	ID3D11BlendState*	m_disableBlendState = nullptr;		//アルファブレンディングを無効にするブレンディングステート。
	ID3D11BlendState*	m_finalBlendState = nullptr;		//最終合成用のブレンディングステート。
	static const int	NumDownSampling = 4;				//ダウンサンプリング回数
	GaussianBlur		m_gaussianblur[NumDownSampling];
	RenderTarget		m_luminanceRT;						//輝度抽出用レンダーターゲット
	RenderTarget		m_blurCombineRT;
	float				resoluteW;							//解像度W
	float				resoluteH;							//解像度H
	Shader				m_vs;								//何もしない頂点シェーダー。
	Shader				m_psLuminance;						//輝度抽出用のピクセルシェーダー。
	Shader				m_psCombine;						//ぼかし画像合成用のピクセルシェーダー。
	Shader				m_psFinal;							//最終合成用のピクセルシェーダー。
	sprite				m_sprite;							//スプライト
	bool				createF = false;					//RTがつくられたフラグ
};