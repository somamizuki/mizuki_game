#pragma once
#include "Player.h"
#include "CollisionDetection.h"
class BossEnemy :public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	BossEnemy(int No, const char* obj_name);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossEnemy();
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
	/// �|�W�V�����̃Q�b�^�[
	/// </summary>
	/// <returns>�|�W�V����(CVector3)</returns>
	const CVector3& GetPos() const
	{
		return m_position;
	}
	/// <summary>
	/// �O�����̃Q�b�^�[
	/// </summary>
	/// <returns>�O����(CVector3)</returns>
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/// <summary>
	/// �E�����̃Q�b�^�[
	/// </summary>
	/// <returns>�E����(CVector3)</returns>
	const CVector3& GetRight() const
	{
		return m_right;
	}
	/// <summary>
	/// ������̃Q�b�^�[
	/// </summary>
	/// <returns>�����(CVector3)</returns>
	const CVector3& GetUp() const
	{
		return m_up;
	}
	/// <summary>
	/// �|�W�V�����̃Q�b�^�[
	/// </summary>
	/// <param name="position">�|�W�V�����̃Z�b�^�[</param>
	void SetPos(CVector3 position)
	{
		m_position = position;
	}


private:
	void Vector();
	void rotmanager();
	/// <summary>
	/// ���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���֐�
	/// </summary>
	/// <param name="dotresult">���ό���(float)</param>
	/// <returns></returns>
	float Acos(float dotresult)
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	Animation		m_animation;							//�A�j���[�V����
	AnimationClip	m_animationClip[1];						//�A�j���[�V�����N���b�v
	SkinModel		m_skinmodel;							//�X�L�����f��
	CVector3		m_position = CVector3::Zero();			//�|�W�V����
	CQuaternion		m_rotation = CQuaternion::Identity();	//��]
	CVector3		m_scale = CVector3::One();				//�X�P�[��
	Player*			m_player = nullptr;						//�v���C���[�̃|�C���^
	CVector3		m_right = CVector3::Right();			//�E����
	CVector3		m_up = CVector3::Up();					//�����
	CVector3		m_forward = CVector3::Front();			//�O����
	CVector3		m_playerpos = CVector3::Zero();			//�v���C���[�̃|�W�V����
	CVector3		m_oldbonepos = CVector3::Zero();		//�O�̃{�[���̃|�W�V����
	
};

