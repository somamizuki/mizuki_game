#pragma once
#include "Player.h"
class m_camera:public GameObject
{
public:
	m_camera(int No,char* obj_name);
	~m_camera();
	bool Start();
	void Update();
	const CVector3& Get_camera_forward() const				//カメラの前方向のゲッター
	{
		return camera_forward;
	}
	const CVector3& Get_camerarite() const					//カメラの右方向のゲッター
	{
		return camera_rite;
	}

	const CVector3 GetPos() const
	{
		return camera_Pos;
	}

	const CVector3 GetXZ()
	{
		return cameraXZ;
	}

private:
	CVector3 player_pos = CVector3::Zero();					//プレイヤーのポジションを格納する

	CVector3 camera_Pos = CVector3::Zero();					//カメラのポジション
	CVector3 camera_Target = CVector3::Zero();				//ターゲット
	CVector3 camera_Up = CVector3::AxisY();					//カメラの上方向
	CVector3 camera_forward = CVector3::Zero();				//カメラの前方向
	CVector3 cameraXZ = CVector3::Zero();
	CVector3 camera_rite = CVector3::Zero();				//カメラの右方向
	CQuaternion camrotX = CQuaternion::Identity();				//回転
	CQuaternion camrotY = CQuaternion::Identity();				//回転
	CVector3 target_to_pos = CVector3::Zero();				//ターゲットからカメラのポジションへ向かうベクトル
	Player* player = nullptr;								//プレイヤーのポインター
	float pad_X = 0.0f;										//パッドの入力量
	float pad_Y = 0.0f;
	float m_angle = 0.0f;									//角度
	float rot_f = 0.0f;										//回転を徐々にさせるための変数
	void Math_Vector();										//いくつかのベクトルの計算
	void Various_Getter();									//様々なゲッター
	void PadInput();										//パッドの入力
	void camera_move();										//
	void camera_stop();

	enum m_state {
		move,
		stop
	};
	m_state move_or_stop = stop;

};

