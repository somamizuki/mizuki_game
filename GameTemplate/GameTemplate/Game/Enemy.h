#pragma once
#include "Player.h"

class enemybullet;
class Enemy:public GameObject
{
public:
	Enemy(int No, const char* obj_name);
	~Enemy();

	bool Start();
	void Update();
	void Draw();
	void PostDraw();
	void Setpos(CVector3 pos)									//�G�l�~�[�̃|�W�V�������Z�b�g
	{
		m_position = pos;
	}
	void Setrot(CQuaternion rot)								//�G�l�~�[�̉�]���Z�b�g
	{
		m_rotation = rot;
	}
	const CVector3& Getforward() const							//�G�l�~�[�̑O����
	{
		return m_forward;
	}
	const CVector3& Getrite() const								//�G�l�~�[�̉E����
	{
		return m_rite;
	}
	const CVector3& Getup() const								//�G�l�~�[�̏����
	{
		return m_up;
	}

	const CVector3& Getpos() const								//�G�l�~�[�̏����
	{
		return m_position;
	}

	const CVector3& Getmovespeed() const								//�G�l�~�[�̏����
	{
		return movespeed;
	}

private:

	void mathVector();								//�O�E��̃x�N�g�����v�Z����֐�
	void enemyMove();								//�G�l�~�[�̈ړ�������֐�
	void SpriteManager();							//�X�v���C�g�̊Ǘ�������֐�

	CVector3 side_vec(CVector3 forward_or_rite);	//�v���C���[�̕�����C�ӂ̎��ɐ����ȕ��ʏ�ɂȂ������x�N�g�������߂�֐�
	float p_angle(CVector3 forward_or_rite);		//�C�ӂ̎����猩���v���C���[�̊p�x�����߂�֐�
	float rot_dir(CVector3 forward_or_rite);		//��]���������߂�֐�
	float Acos(float t)					//acosf()�ŁA1.0f�����傫������
	{									//�n���Ȃ��悤�ɂ��邽�߂̃��b�v�֐��B
		t = min(1.0f, max(-1.0f,t));
		return t;
	}

	bool posinScreen = false;					//�X�v���C�g��`�悷�邩�ǂ����̃t���O
	

	/*�G�l�~�[�̃f�[�^�i���f���A�|�W�V�����A��]�Ȃǁj�B*/
	SkinModel m_model;											//�X�L�����f��
	CVector3 m_position = CVector3::Zero();						//�|�W�V����
	CVector3 targetPos = CVector3::Zero();						//�^�[�Q�b�g�̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();			//��]
	/*�G�l�~�[�̑O�A�E�A��*/
	CVector3 m_forward = CVector3::Zero();						//�O
	CVector3 m_rite = CVector3::Zero();							//�E
	CVector3 m_up = CVector3::Zero();							//��

	CVector3 movespeed = CVector3::Zero();						//�ړ����x
	float speed = 0.0f;
	Player* m_player = nullptr;									//�v���C���[�̃|�C���^�[
	bool atack_f = false;										//�U���t���O
	std::vector<enemybullet*> m_bullet;							//�G�l�~�[�̒e�̔z��
	ShaderResourceView shaderResource;							//�G�l�~�[�̈ʒu�\���X�v���C�g�̃V�F�[�_�[���\�[�X
	ShaderResourceView matoshaderResource;						//�܂Ƃ̃V�F�[�_�[���\�[�X

	sprite sprite_ins;//�G�l�~�[�̈ʒu�\���X�v���C�g
	sprite mato;//�܂�
};

