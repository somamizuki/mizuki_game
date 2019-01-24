#pragma once
#include"Shader.h"
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();
	void Init(ID3D11ShaderResourceView* SRV);
	void Draw(sprite* postEffectSprite,ID3D11ShaderResourceView* srv);

	ID3D11ShaderResourceView* GetResultTextureSRV()
	{
		return m_downsampleRT[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
private:
	void UpdateWeights();
	float m_blurIntensity = 50.0f;							//ブラーの強さ。ブラーのウェイトの計算で使用されます。
	enum EnRenderTarget {
		enRenderTarget_XBlur,		//Xブラーの書き込み先となるレンダリングターゲット。
		enRenderTarget_YBlur,		//Yブラーの書き込み先となるレンダリングターゲット。
		enRenderTarget_Num,			//レンダリングターゲットの枚数。
	};
	static const int NUM_WEIGHTS = 8;	//カウスフィルタの重みの数。
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};
	ID3D11ShaderResourceView* m_SRV;
	static const int NumDownSampling = 1;					//ダウンサンプリング回数
	RenderTarget m_downsampleRT[enRenderTarget_Num];		//ダウンサンプリング用のレンダリングターゲット
	//D3D11_VIEWPORT m_downsampleVP[NumDownSampling];		//ダウンサンプリング用のビューポート
	float resoluteW;										//解像度W
	float resoluteH;										//解像度H
	Shader m_vsXBlur;						//Xブラー用の頂点シェーダー。
	Shader m_vsYBlur;						//Yブラー用の頂点シェーダー。
	Shader m_psBlur;						//ブラー用のピクセルシェーダー。
	SBlurParam m_blurParam;						//ブラー用のパラメータ。
	ConstantBuffer m_blurCbGpu;				//ブラー用の定数バッファ(GPU側)
};

