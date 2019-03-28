#pragma once
class missileRechargeHUD
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	missileRechargeHUD();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~missileRechargeHUD();
	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="waku_filepath">�gL"filepath"</param>
	/// <param name="filepath">���[�^�[L"filepath"</param>
	/// <param name="W">��</param>
	/// <param name="H">����</param>
	void Init(const wchar_t* waku_filepath, const wchar_t* filepath, float W, float H);
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	/// <param name="position">�|�W�V����(CVector3)</param>
	/// <param name="m_rotation">���[�e�[�V����(CQuaternion)</param>
	/// <param name="Gaugelevel">�Q�[�W���x��(float)</param>
	void Update(CVector3 position, CQuaternion m_rotation, float Gaugelevel);
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
private:
	ShaderResourceView	m_SRV;				//���[�^�[��SRV
	ShaderResourceView	m_waku_SRV;			//�g��SRV
	sprite				m_waku_sprite;		//�g�̃X�v���C�g
	sprite				m_sprite;			//���[�^�[�̃X�v���C�g
};

