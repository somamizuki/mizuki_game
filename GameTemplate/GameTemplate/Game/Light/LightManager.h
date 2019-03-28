#pragma once
class LightManager:Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	LightManager();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LightManager();
	/// <summary>
	/// ���C�g�̍X�V
	/// </summary>
	void LightExecute();
	/// <summary>
	/// ���C�g�p�����[�^�[���Z�b�g
	/// </summary>
	/// <param name="ligparam">ligParam</param>
	void SetLightParam(ligParam& ligparam);
	void DeleteLight(LightBase* light)
	{
		for (auto& lig : anyLight)
		{
			if (lig == light)
			{
				anyLight.erase(std::remove(anyLight.begin(), anyLight.end(), lig), anyLight.end());
			}
		}
	}
	/// <summary>
	/// �f�B���N�V�������C�g�܂��̓|�C���g���C�g��o�^����֐�
	/// </summary>
	/// <param name="light"></param>
	void PushLight(LightBase* light)
	{
		if (anyLight.size() == 0)
		{
			anyLight.push_back(light);
		}
		else 
		{
			for (auto& ligIT : anyLight)
			{
				if (ligIT->GetLightType() != light->GetLightType())
				{
					anyLight.push_back(light);
				}
				else if(ligIT->GetLightType() == light->GetLightType())
				{
					throw;
				}
			}
		}
	}


private:
	std::vector<LightBase*> anyLight;
};

