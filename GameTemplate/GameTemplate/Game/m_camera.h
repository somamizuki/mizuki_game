#pragma once

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

	const CVector3 GetPos() const							//カメラのポジションのゲッター
	{
		return camera_Pos;
	}

	const CVector3 GetXZ() const							//気にしない
	{
		return cameraXZ;
	}
	
private:
	void CameraMove();										//カメラの動きを管理する関数





	CVector3 player_pos = CVector3::Zero();					//プレイヤーのポジションを格納する

	CVector3 camera_Pos = CVector3::Zero();					//カメラのポジション
	CVector3 camera_Target = CVector3::Zero();				//ターゲット
	CVector3 camera_Up = CVector3::Zero();					//カメラの上方向
	CVector3 camera_forward = CVector3::Zero();				//カメラの前方向
	CVector3 cameraXZ = CVector3::Zero();
	CVector3 camera_rite = CVector3::Zero();				//カメラの右方向
	CQuaternion camrotX = CQuaternion::Identity();				//回転
	CQuaternion camrotY = CQuaternion::Identity();				//回転
	CVector3 target_to_pos = CVector3::Zero();				//ターゲットからカメラのポジションへ向かうベクトル




	Player* player = nullptr;								//プレイヤーのポインター
	float pad_X = 0.0f;										//パッドの入力量
	float pad_Y = 0.0f;
	float oldrot = 0.0f;
	float rotYmax = 0.0f;
	float rotXmax = 0.0f;
	float m_angleY = 0.0f;									//角度
	float m_angleX = 0.0f;
	float rot_f = 0.0f;										//回転を徐々にさせるための変数
	float CamLen = 0.0f;
	void Math_Vector();										//いくつかのベクトルの計算
	void Various_Getter();									//様々なゲッター
	void PadInput();										//パッドの入力

};

