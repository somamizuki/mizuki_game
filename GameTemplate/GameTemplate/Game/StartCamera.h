#pragma once
class StartCamera:GameObject
{
public:
	StartCamera(int No, const char* obj_name);
	~StartCamera();
	bool Start();
	void Update();
private:
	CVector3 m_position = CVector3::Zero();
	CVector3 m_up = CVector3::Up();

};

