#pragma once
class game_stage
{
public:
	game_stage();
	~game_stage();
	bool Start();
	void Update();
	void Draw();
private:
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();

};