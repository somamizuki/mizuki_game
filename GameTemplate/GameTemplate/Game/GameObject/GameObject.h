#pragma once
//#include "GameObjectManajer.h"
class GameObject:Noncopyable
{
public:
	//優先度,オブジェクトの名前
	GameObject(int No, const char* obj_name);
	//{
	//	game_obj.Set_push_list(this, No);
	//	this_name = obj_name;
	//}
	virtual ~GameObject()
	{

	}
	virtual bool Start() { return true; }
	virtual void Update(){}
	virtual void Draw(){}
	const char* GetName()
	{
		return this_name;
	}
	bool Get_isStart()
	{
		return m_start;
	}
	void Set_isStart(bool start_f)
	{
		m_start = start_f;
	}
private:
	const char* this_name;
	bool m_start = false;

};

