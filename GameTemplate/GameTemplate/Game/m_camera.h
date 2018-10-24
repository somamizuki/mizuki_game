#pragma once
#include "Player.h"
class m_camera:public GameObject
{
public:
	m_camera(int No,char* obj_name);
	~m_camera();
	bool Start();
	void Update();
	const CVector3& Get_camera_forward() const				//�J�����̑O�����̃Q�b�^�[
	{
		return camera_forward;
	}
	const CVector3& Get_camerarite() const					//�J�����̉E�����̃Q�b�^�[
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
	CVector3 player_pos = CVector3::Zero();					//�v���C���[�̃|�W�V�������i�[����

	CVector3 camera_Pos = CVector3::Zero();					//�J�����̃|�W�V����
	CVector3 camera_Target = CVector3::Zero();				//�^�[�Q�b�g
	CVector3 camera_Up = CVector3::AxisY();					//�J�����̏����
	CVector3 camera_forward = CVector3::Zero();				//�J�����̑O����
	CVector3 cameraXZ = CVector3::Zero();
	CVector3 camera_rite = CVector3::Zero();				//�J�����̉E����
	CQuaternion camrotX = CQuaternion::Identity();				//��]
	CQuaternion camrotY = CQuaternion::Identity();				//��]
	CVector3 target_to_pos = CVector3::Zero();				//�^�[�Q�b�g����J�����̃|�W�V�����֌������x�N�g��
	Player* player = nullptr;								//�v���C���[�̃|�C���^�[
	float pad_X = 0.0f;										//�p�b�h�̓��͗�
	float pad_Y = 0.0f;
	float m_angle = 0.0f;									//�p�x
	float rot_f = 0.0f;										//��]�����X�ɂ����邽�߂̕ϐ�
	void Math_Vector();										//�������̃x�N�g���̌v�Z
	void Various_Getter();									//�l�X�ȃQ�b�^�[
	void PadInput();										//�p�b�h�̓���
	void camera_move();										//
	void camera_stop();

	enum m_state {
		move,
		stop
	};
	m_state move_or_stop = stop;

};

