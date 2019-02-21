#pragma once
class missileRechargeHUD
{
public:
	missileRechargeHUD();
	~missileRechargeHUD();
	void Init(const wchar_t* waku_filepath, const wchar_t* filepath, float W, float H);
	void Update(CVector3 position, CQuaternion m_rotation, float Gaugelevel);
	void Draw();
private:
	ShaderResourceView m_SRV;
	ShaderResourceView m_waku_SRV;
	sprite m_waku_sprite;
	sprite m_sprite;

};

