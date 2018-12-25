#pragma once

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

	const CVector3 GetPos() const							//�J�����̃|�W�V�����̃Q�b�^�[
	{
		return camera_Pos;
	}

	const CVector3 GetXZ() const							//�C�ɂ��Ȃ�
	{
		return cameraXZ;
	}
	
private:
	void CameraMove();										//�J�����̓������Ǘ�����֐�





	CVector3 player_pos = CVector3::Zero();					//�v���C���[�̃|�W�V�������i�[����

	CVector3 camera_Pos = CVector3::Zero();					//�J�����̃|�W�V����
	CVector3 camera_Target = CVector3::Zero();				//�^�[�Q�b�g
	CVector3 camera_Up = CVector3::Zero();					//�J�����̏����
	CVector3 camera_forward = CVector3::Zero();				//�J�����̑O����
	CVector3 cameraXZ = CVector3::Zero();
	CVector3 camera_rite = CVector3::Zero();				//�J�����̉E����
	CQuaternion camrotX = CQuaternion::Identity();				//��]
	CQuaternion camrotY = CQuaternion::Identity();				//��]
	CVector3 target_to_pos = CVector3::Zero();				//�^�[�Q�b�g����J�����̃|�W�V�����֌������x�N�g��




	Player* player = nullptr;								//�v���C���[�̃|�C���^�[
	float pad_X = 0.0f;										//�p�b�h�̓��͗�
	float pad_Y = 0.0f;
	float oldrot = 0.0f;
	float rotYmax = 0.0f;
	float rotXmax = 0.0f;
	float m_angleY = 0.0f;									//�p�x
	float m_angleX = 0.0f;
	float rot_f = 0.0f;										//��]�����X�ɂ����邽�߂̕ϐ�
	float CamLen = 0.0f;
	void Math_Vector();										//�������̃x�N�g���̌v�Z
	void Various_Getter();									//�l�X�ȃQ�b�^�[
	void PadInput();										//�p�b�h�̓���

};

