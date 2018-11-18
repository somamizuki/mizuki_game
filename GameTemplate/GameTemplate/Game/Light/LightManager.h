#pragma once
class LightManager:Noncopyable
{
public:
	LightManager();
	~LightManager();

	void LightExecute();
	void SetLightParam(ligParam& ligparam);

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

