#pragma once
using namespace Light;

class LightBase:Noncopyable
{
public:
	LightBase();

	virtual bool InitLightSB() { return true; }
	virtual void UpdateSubresource(){}
	virtual void SendStructuredBuffer(){}

	void SetisInit(bool InitF)
	{
		isInit = InitF;
	}

	bool GetisInit()
	{
		return isInit;
	}

	void SetInitStruct(bool initf)
	{
		InitStruct = initf;
	}
	bool GetInitStruct()
	{
		return InitStruct;
	}

	void SetLightType(LightType lig)
	{
		ligtype = lig;
	}

	const LightType& GetLightType()
	{
		return ligtype;
	}

private:
	bool isInit = false;
	bool InitStruct = false;
	LightType ligtype = nolig;


};


