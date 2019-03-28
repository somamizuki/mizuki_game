#pragma once
class Result
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Result();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Result();
	/// <summary>
	/// �������֐�
	/// </summary>
	void Init();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �G�l�~�[�����񂾐����Z�b�g
	/// </summary>
	void SetKnockDownEnemySUM()
	{
		KnockDownEnemySUM++;
	}
	/// <summary>
	/// �c��HP���Z�b�g
	/// </summary>
	/// <param name="HP"></param>
	void SetRemHP(int HP)
	{
		RemHP = HP;
	}
	/// <summary>
	/// �c�蕪���Z�b�g
	/// </summary>
	/// <param name="Min">��(int)</param>
	void SetRemMIN(int Min)
	{
		RemMIN = Min;
	}
	/// <summary>
	/// �c��b���Z�b�g
	/// </summary>
	/// <param name="Sec">�b(float)</param>
	void SetRemSEC(float Sec)
	{
		RemSEC = Sec;
	}
	/// <summary>
	/// �Q�[���N���A�t���O���Z�b�g
	/// </summary>
	/// <param name="flag">bool</param>
	void SetGameClear(bool flag)
	{
		GameClear = flag;
		if (GameClear)
		{
			ClearBonus = 100;
		}
	}
	/// <summary>
	/// �^�C���A�b�v�t���O���Z�b�g
	/// </summary>
	/// <param name="timeup">bool</param>
	void SetTimeUP(bool timeup)
	{
		isTimeUP = timeup;
	}
private:
	Font m_font[7];					//�t�H���g
	int KnockDownEnemySUM = 0;		//�G�l�~�[�����񂾐����Z�b�g
	int RemHP = 0;					//�c���HP���Z�b�g
	int RemMIN = 0;					//�c��̕����Z�b�g
	float RemSEC = 0.0f;			//�c��̕b
	bool GameClear = false;			//�Q�[���N���A�t���O
	bool isTimeUP = false;			//�^�C���A�b�v�t���O
	int ClearBonus = 0;				//�N���A�{�[�i�X
	int ResultPoint = 0;			//���v���_
};

