#pragma once
class LightManager:Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LightManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~LightManager();
	/// <summary>
	/// ライトの更新
	/// </summary>
	void LightExecute();
	/// <summary>
	/// ライトパラメーターをセット
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
	/// ディレクションライトまたはポイントライトを登録する関数
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

