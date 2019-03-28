#pragma once
class Effect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Effect();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Effect();
	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="filepath">L"filepath"</param>
	void Init(const wchar_t* filepath);
	/// <summary>
	/// �G�t�F�N�g�Đ��֐�
	/// </summary>
	/// <param name="position">�|�W�V����(CVector3)</param>
	/// <param name="scale">�X�P�[��(CVector3)</param>
	void Play(CVector3 position, CVector3 scale);
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
private:
	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager*	m_effekseerManager = nullptr;				//�G�t�F�N�g�}�l�[�W���[
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;		//�G�t�F�N�T�[�����_�[
	Effekseer::Effect* m_sampleEffect = nullptr;					//�G�t�F�N�g
	Effekseer::Handle m_playEffectHandle = -1;						//�G�t�F�N�g�n���h��
};

