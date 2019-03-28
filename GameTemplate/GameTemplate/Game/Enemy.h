#pragma once
#include"ObjectInfo.h"
#include"SpriteEffect.h"
#include"level/Level.h"


class Player;
class Class_of_NewGO;
class bullet;
using namespace BulletInfo;
class Enemy :public GameObject
{
public:
	/// <summary>
	/// �G�l�~�[�̃R���X�g���N�^
	/// </summary>
	/// <param name="No">�D��x</param>
	/// <param name="obj_name">���O</param>
	Enemy(int No, const char* obj_name);
	/// <summary>
	/// �G�l�~�[�̃f�X�g���N�^
	/// </summary>
	~Enemy();
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns>bool</returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �G�t�F�N�g�̕`��
	/// </summary>
	void EffectDraw();
	/// <summary>
	/// ��O�ɕ`�悵�������̂̕`��
	/// </summary>
	void PostDraw();
	/// <summary>
	/// Delete���ɌĂ΂��֐�
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// �|�W�V�������Z�b�g
	/// </summary>
	/// <param name="pos">�|�W�V����(CVector3)</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]���Z�b�g
	/// </summary>
	/// <param name="rot">��](CQuaternion)</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �O����
	/// </summary>
	/// <returns>�O����(CVector3)</returns>
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/// <summary>
	/// �E����
	/// </summary>
	/// <returns>�E����(CVector3)</returns>
	const CVector3& GetRite() const
	{
		return m_rite;
	}
	/// <summary>
	/// �����
	/// </summary>
	/// <returns>�����(CVector3)</returns>
	const CVector3& GetUp() const
	{
		return m_up;
	}
	/// <summary>
	/// �G�l�~�[�̃|�W�V����
	/// </summary>
	/// <returns>�|�W�V����(CVector3)</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �G�l�~�[�̈ړ����x
	/// </summary>
	/// <returns>�ړ����x(CVector3)</returns>
	const CVector3& GetMoveSpeed() const
	{
		return m_movespeed;
	}
	/// <summary>
	/// �G�l�~�[�̉�]
	/// </summary>
	/// <returns>��](CQuaternion)</returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

private:
	/// <summary>
	/// �O�E��̃x�N�g�����v�Z����֐�
	/// </summary>
	void Vector();
	/// <summary>
	/// �G�l�~�[�̈ړ�������֐�
	/// </summary>
	void EnemyMove();
	/// <summary>
	/// �X�v���C�g�̊Ǘ�������֐�
	/// </summary>
	void SpriteManager();
	/// <summary>
	/// �o���b�g�}�l�[�W���[
	/// </summary>
	void BulletManager();
	/// <summary>
	/// �v���C���[�̕�����C�ӂ̎��ɐ����ȕ��ʏ�ɂȂ������x�N�g�������߂�֐�
	/// </summary>
	CVector3 SideVec(CVector3 forward_or_rite);
	/// <summary>
	/// �C�ӂ̎����猩���v���C���[�̊p�x�����߂�֐�
	/// </summary>
	float ToPlayerAngle(CVector3 forward_or_rite);
	/// <summary>
	/// ��]���������߂�֐�
	/// </summary>
	float RotDirection(CVector3 forward_or_rite);
	/// <summary>
	/// acosf()�ŁA1.0f�����傫������n���Ȃ��悤�ɂ��邽�߂̃��b�v�֐��B
	/// </summary>
	/// <param name="t">���ό���(float)</param>
	/// <returns>float</returns>
	float Acos(float t)
	{
		t = min(1.0f, max(-1.0f, t));
		return t;
	}

	bool						m_posinscreen = false;					//�X�v���C�g��`�悷�邩�ǂ����̃t���O
	bool						m_enemymarkerdraw = false;				//�G�l�~�[�̃}�[�J�[��`�悷�邩�̃t���O


	/*�G�l�~�[�̃f�[�^�i���f���A�|�W�V�����A��]�Ȃǁj�B*/
	SkinModel					m_skinmodel;							//�X�L�����f��
	CVector3					m_position = CVector3::Zero();			//�|�W�V����
	CQuaternion					m_rotation = CQuaternion::Identity();	//��]
	/*�G�l�~�[�̑O�A�E�A��*/
	CVector3					m_forward = CVector3::Zero();			//�O
	CVector3					m_rite = CVector3::Zero();				//�E
	CVector3					m_up = CVector3::Zero();				//��

	CVector3					m_movespeed = CVector3::Zero();			//�ړ����x
	float						m_nowspeed = 0.0f;
	Player*						m_player = nullptr;						//�v���C���[�̃|�C���^�[
	ShaderResourceView			m_outscreenenemySRV;					//�G�l�~�[�̈ʒu�\���X�v���C�g�̃V�F�[�_�[���\�[�X
	ShaderResourceView			m_enemymarkerSRV;						//�܂Ƃ̃V�F�[�_�[���\�[�X

	sprite						m_outenemysprite;						//�G�l�~�[�̈ʒu�\���X�v���C�g
	sprite						m_enemymarkersprite;					//�}�[�J�[
	Class_of_NewGO*				m_class_of_newgo = nullptr;				//�N���X�I�u�j���[�S�[�̃|�C���^�[


	const float					BULLETSPAN = 3.0f;						//�o���b�g�𔭎˂���Ԋu
	float						m_ritebullettime = 0.0f;				//�E�o���b�g�̃^�C�}�[
	float						m_leftbullettime = 0.0f;				//���o���b�g�̃^�C�}�[

	bullet*						m_ritebullet = nullptr;					//�E�~�T�C���̃|�C���^�[
	bullet*						m_leftbullet = nullptr;					//���~�T�C���̃|�C���^�[
	Level						m_enemyenginlevel;						//�G�l�~�[�̃W�F�b�g�̃|�W�V������������
	struct Engin	//�X�v���C�g�G�t�F�N�g�ƃW�F�b�g�̃|�W�V�������������\����
	{
		SpriteEffect	m_spriteeffect;
		CVector3		m_toengin;
	};
	std::vector<Engin*>			m_spriteeffect;							//Engin��level�ɓo�^���ꂽ�������ςރ��X�g(vector)
	ShaderResourceView			m_effectsrv;							//�X�v���C�g�G�t�F�N�g�Ɏg��SRV
};

