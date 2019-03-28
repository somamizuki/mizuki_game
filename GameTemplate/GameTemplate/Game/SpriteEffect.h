#pragma once
class SpriteEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SpriteEffect();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	~SpriteEffect();
	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="SRV">SRV(ID3D11ShaderResourceView*)</param>
	/// <param name="time">�����鎞��(float)</param>
	/// <param name="span">�����p�x�t���[��(int)</param>
	void Init(ID3D11ShaderResourceView* SRV, float time, int span);
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	/// <param name="position">����������|�W�V����</param>
	void Update(CVector3& position);
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
private:
	/// <summary>
	/// �X�v���C�g�𔭐�������֐�
	/// </summary>
	/// <param name="position">CVector3</param>
	void GenerateSprite(CVector3 position);
	/// <summary>
	/// ���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���B
	/// </summary>
	/// <param name="dotresult">���ό���(float)</param>
	/// <returns>�p�x���W�A��(float)</returns>
	float Acos(float dotresult)
	{
		float angle = acosf(min(1.0f, max(-1.0f, dotresult)));
		return angle;
	}

private:
	/// <summary>
	/// EffectSprite�̍\����
	/// </summary>
	struct SEffectSprite{
		sprite m_sprite;
		CVector3 m_position = CVector3::Zero();
		CVector3 m_forward = CVector3::AxisZ()*-1.0f;
		CVector3 m_rite = CVector3::AxisX()*-1.0f;
		CVector3 m_up = CVector3::AxisY();
		float size = 0.2f;
		float time = 0.0f;
		bool dethflag = false;
		bool Initflag = false;
	};

	std::list<SEffectSprite*> EffectSpriteList;		//SEffectSprite�̔z��
	ID3D11ShaderResourceView* m_SRV;				//�X�v���C�g��SRV
	float m_time = 0.0f;							//�o�ߎ���
	float changesize = 0.0f;						//�X�v���C�g�̊g��k��
	float eraseTime;								//�����鎞��
	int m_frame = 0;								//�o�߃t���[��
	int m_Span;										//�����p�x�t���[��
};

