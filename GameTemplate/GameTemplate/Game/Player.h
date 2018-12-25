#pragma once

class m_camera;
class bullet;
class Player:public GameObject
{
public:
	Player(int No, const char* obj_name);
	~Player();
	bool Start();								//�X�^�[�g�֐�
	void Update();								//�A�b�v�f�[�g�֐�
	void Draw();								//�`��֐�
	void PostDraw();							//��O�ɕ`�悵�������̂̕`��
	void setposition(CVector3 pos)				//�|�W�V�����̃Z�b�^�[
	{
		m_position = pos;
	}
	void setrot(CQuaternion rot)				//��]�̃Z�b�^�[
	{
		m_rotation = rot;
	}
	const CVector3& Getpos() const				//�|�W�V�����̃Q�b�^�[
	{
		return m_position;
	}

	const CVector3& Getforward() const			//�O�����̃Q�b�^�[
	{
		return m_forward;
	}

	const CVector3& Getrite() const				//�E�����̃Q�b�^�[
	{
		return m_rite;
	}

	const CVector3& Getup() const				//������̃Q�b�^�[
	{
		return m_up;
	}

	const CVector3& Get_PlayerMove() const		//�v���C���[�̈ړ����x�̃Q�b�^�[
	{
		return movespeed;
	}

	
private:
	SkinModel m_model;									//�X�L�����f���B

	

	CVector3 m_position = CVector3::Zero();				//�v���C���[�̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 movespeed = CVector3::Zero();				//movespeed
	CMatrix rot_M;
	CVector3 m_forward;
	CVector3 m_rite;
	CVector3 m_up;
	ShaderResourceView shaderResource;
	sprite aim;

	float pad_X;									//�p�b�hX�̓��͗�
	float pad_Y;									//�p�b�hY�̓��͗�
	float defaultspeed = 4000.0f;					//�f�t�H���g�̑��x
	float boostspeed = 8000.0f;						//�u�[�X�g���̑��x
	float slowspeed = 2000.0f;						//�X���[�X�s�[�h
	float rotspeedX = 2.0f;							//X������̉�]�X�s�[�h
	float rotspeedZ = 2.0f;							//Z������̉�]�X�s�[�h
	float bityousei = 0.3f;							//�G�C�������������ϐ�

	void playermove();								//�v���C���[�̈ړ��֐�
	void playerreturn();
	void vector();									//�v���C���[�̑O�E��̃x�N�g�����v�Z����֐�
	float Acos(float t)					//acosf()�ŁA1.0f�����傫������
	{									//�n���Ȃ��悤�ɂ��邽�߂̃��b�v�֐��B
		t = min(1.0f, max(-1.0f, t));
		return t;
	}


	m_camera* camera = nullptr;						//�J�����̃|�C���^�[

	std::vector<bullet*> m_bullet;					//�ʂ̔z��
	enum PlayerState								//�v���C���[�̃X�e�[�g
	{
		Nomal,		//�ʏ�
		Return		//���_�ɖ߂�(�~�b�V�����͈͂𒴂�����)
	};
	PlayerState pState = Nomal;
};

