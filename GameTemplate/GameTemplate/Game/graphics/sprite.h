#pragma once
#include"ShaderResourceView.h"
#include"UnorderedAccessView.h"
#include"Primitive.h"
#include"ConstantBuffer.h"
#include"StructuredBuffer.h"

class sprite:Noncopyable
{
public:
	static const CVector2 DEFAULT_PIVOT;	//デフォルトピポット
	/// <summary>
	/// コンストラクタ
	/// </summary>
	sprite();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~sprite();
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="tex">ID3D11ShaderResourceView*</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void Init(ID3D11ShaderResourceView* tex, float w, float h);
	/// <summary>
	/// フルスクリーン描画用の初期化関数
	/// </summary>
	void FullScreenInit();
	/// <summary>
	/// リリース関数
	/// </summary>
	void Release();
	/// <summary>
	/// シェーダーのセッター
	/// </summary>
	/// <param name="filepathVS">VSシェーダー(L"filepath")</param>
	/// <param name="filepathPS">PSシェーダー(L"filepath")</param>
	void SetShader(const char* filepathVS, const char* filepathPS)
	{
		m_ps.Load(filepathPS, "PSMain", Shader::EnType::PS);
		m_vs.Load(filepathVS, "VSMain", Shader::EnType::VS);
	}
	/// <summary>
	///	シェーダーのセッター
	/// </summary>
	/// <param name="VS">Shader* VS</param>
	/// <param name="PS">Shader* PS</param>
	void SetShader(Shader* VS, Shader* PS)
	{
		m_ps = *PS;
		m_vs = *VS;
	}
	/// <summary>
	/// テクスチャーのセッター
	/// </summary>
	/// <param name="tex">ID3D11ShaderResourceView* tex</param>
	void SetTexture(ID3D11ShaderResourceView* tex)
	{
		m_textureSRV = tex;
	}
	/// <summary>
	/// ビュー行列とプロジェクション行列のセッター
	/// </summary>
	/// <param name="viewM">ビュー行列(CMatrix)</param>
	/// <param name="projM">プロジェクション行列(CMatrix)</param>
	void SetViewProj(CMatrix& viewM,CMatrix& projM)
	{
		m_view = viewM;
		m_proj = projM;
	}
	/// <summary>
	/// プロジェクション行列のセッター
	/// </summary>
	/// <param name="projM">プロジェクション行列(CMatrix)</param>
	void SetProj(CMatrix& projM)
	{
		m_proj = projM;
	}
	/// <summary>
	/// カラーのセッター(α値の調整など)
	/// </summary>
	/// <param name="mulColor">const CVector4& mulColor</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}
	/// <summary>
	/// アップデート関数
	/// </summary>
	/// <param name="trans">平行移動(CVector3)</param>
	/// <param name="rot">回転(CQuaternion)</param>
	/// <param name="scale">スケール(CVector3)</param>
	/// <param name="pivot">ピポット(CVector2)</param>
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="renderContext">ID3D11DeviceContext</param>
	void Draw(ID3D11DeviceContext& renderContext);
	/// <summary>
	/// ポストエフェクトの描画関数
	/// </summary>
	/// <param name="renderContext">ID3D11DeviceContext</param>
	void PostEffectDraw(ID3D11DeviceContext& renderContext);
private:
	/// <summary>
	/// スプライトの構造体
	/// </summary>
	struct SSpriteCB {
		CMatrix WVP;
		CVector4 mulColor;
	};
	CVector3					m_position = CVector3::Zero();			//ポジション
	CQuaternion					m_rotation = CQuaternion::Identity();	//回転
	CVector3					m_scale = CVector3::One();				//スケール
	CMatrix						m_world = CMatrix::Identity();			//ワールド行列
	Shader						m_ps;									//ピクセルシェーダー
	Shader						m_vs;									//頂点シェーダー
	CVector4					m_mulColor = CVector4::White();			//カラー
	Primitive					m_primitive;							//プリミティブ
	ID3D11ShaderResourceView*	m_textureSRV = nullptr;					//テクスチャーのSRV
	ConstantBuffer				m_cb;									//定数バッファー
	ID3D11SamplerState*			m_samplerState = nullptr;				//サンプラーステート
	CVector2					m_size = CVector2::Zero();				//サイズ
	CMatrix						m_view;									//ビュー行列
	CMatrix						m_proj;									//プロジェクション行列
	bool						f_update = false;						//アップデート関数が呼ばれたフラグ
};

