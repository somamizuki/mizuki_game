#pragma once
#include "Font.h"
class Timer//:public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Timer();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Timer();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �X�g�b�v�֐�
	/// </summary>
	void Stop()
	{
		StopTimer = true;
	}
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	void Start()
	{
		StopTimer = false;
	}
	/// <summary>
	/// ���̃Q�b�^�[
	/// </summary>
	/// <returns>int</returns>
	int GetMIN()
	{
		return m_minits;
	}
	/// <summary>
	/// �b�̃Q�b�^�[
	/// </summary>
	/// <returns>float</returns>
	float GetSEC()
	{
		return m_seconds;
	}
	/// <summary>
	/// �^�C���A�b�v�����H
	/// </summary>
	/// <returns>bool</returns>
	bool IsTIMEUP()
	{
		return TimeUP;
	}

private:
	Font	m_font;					//�t�H���g
	bool	StopTimer = false;		//�^�C�}�[��~�t���O
	bool	TimeUP = false;			//�^�C���A�b�v�t���O
	float	m_seconds = 30.0f;		//�b
	int		m_minits = 1;			//��
};

