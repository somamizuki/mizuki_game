#pragma once
#include "level/Level.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"
class game_start:public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	game_start(int No, const char* obj_name);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~game_start();
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns>bool</returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// UI描画関数
	/// </summary>
	void UIDraw();
	/// <summary>
	/// Delete時に呼ばれる関数
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// ゲームスタートフラグのゲッター
	/// </summary>
	/// <returns>bool</returns>
	bool GetGameStartflag()
	{
		return m_gamestart;
	}
private:
	CSoundSource	m_bgm;												//BGM
	CSoundSource	m_selectSE;											//セレクトSE
	CSoundSource	m_decisionSE;										//決定SE
	bool			m_startflag = false;								//スタートフラグ
	enum MenuState {
		start,
		howtocontrol
	};
	MenuState		m_select = start;									//メニューステート
	sky*			m_cubemap = nullptr;								//キューブマップ
	Level			m_level;											//レベルのインスタンス
	CVector3		m_lightcameradir = CVector3::Zero();				//ライトカメラディレクション
	SPointLight		m_spointlight;										//ポイントライトの構造体
	CPointLight		m_pointlig;											//ポイントライト
	SkinModel		m_sikinmodel;										//スキンモデル
	CVector3		m_position;											//ポジション
	CQuaternion		m_rotation = CQuaternion::Identity();				//回転
	CVector3		m_cameraposition = CVector3::Zero();				//カメラのポジション
	bool			m_gamestart = false;								//ゲームスタートフラグ
	Font			m_font;												//フォント
	const CVector4	m_selectedstringcolor = {0.0f,1.0f,0.0f,1.0f};		//選択されたフォントのカラー
	const CVector4	m_noselectstringcolor = { 0.0f,1.0f,0.0f,0.2 };		//選択されていないフォントのカラー
};

