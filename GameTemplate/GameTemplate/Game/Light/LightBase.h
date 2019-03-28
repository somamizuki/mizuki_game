#pragma once
using namespace Light;

class LightBase:Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	LightBase();
	/// <summary>
	/// �X�g���N�`���[�h�o�b�t�@�[�̃C�j�b�g
	/// </summary>
	/// <returns>bool</returns>
	virtual bool InitLightSB() { return true; }
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	virtual void UpdateSubresource(){}
	/// <summary>
	/// �X�g���N�`���[�h�o�b�t�@�[�𑗂�
	/// </summary>
	virtual void SendStructuredBuffer(){}
	/// <summary>
	/// �C�j�b�g���ꂽ���ǂ����̃t���O���Z�b�g
	/// </summary>
	/// <param name="InitF">bool</param>
	void SetisInit(bool InitF)
	{
		isInit = InitF;
	}
	/// <summary>
	/// �C�j�b�g���ꂽ���ǂ����̃t���O���Q�b�g
	/// </summary>
	/// <returns>bool</returns>
	bool GetisInit()
	{
		return isInit;
	}
	/// <summary>
	/// �\���̂����������ꂽ���ǂ����̃t���O���Z�b�g
	/// </summary>
	/// <param name="initf">bool</param>
	void SetInitStruct(bool initf)
	{
		InitStruct = initf;
	}
	/// <summary>
	/// �\���̂����������ꂽ���ǂ����̃t���O���Q�b�g
	/// </summary>
	/// <returns>bool</returns>
	bool GetInitStruct()
	{
		return InitStruct;
	}
	/// <summary>
	/// ���C�g�̃^�C�v���Z�b�g
	/// </summary>
	/// <param name="lig">LightType</param>
	void SetLightType(LightType lig)
	{
		ligtype = lig;
	}
	/// <summary>
	/// ���C�g�^�C�v�̃Q�b�^�[
	/// </summary>
	/// <returns>LightType</returns>
	const LightType& GetLightType()
	{
		return ligtype;
	}

private:
	bool		isInit = false;			//�������t���O
	bool		InitStruct = false;		//�X�g���N�`���[�h�o�b�t�@�[�̏������t���O
	LightType	ligtype = nolig;		//���C�g�^�C�v
	


};


