#include "stdafx.h"
#include "HPGaugeHUD.h"

namespace {
	//ゲージの量幅は３ピクセル枠より小さい。
	const float GUAGE_PIXEL_HALF_OFFSET = 6;
}
HPGaugeHUD::HPGaugeHUD()
{
}


HPGaugeHUD::~HPGaugeHUD()
{
}




void HPGaugeHUD::Init(const wchar_t* waku_filepath, const wchar_t* filepath, float W, float H)
{
	m_waku_SRV.CreateFromDDSTextureFromFile(waku_filepath);
	m_SRV.CreateFromDDSTextureFromFile(filepath);

	m_waku_sprite.Init(m_waku_SRV.GetBody(), W, H);
	//ゲージの中だけで描くために、ゲージは枠よりGUAGE_PIXEL_HALF_OFFSET＊２ピクセル分小さくする。
	m_sprite.Init(m_SRV.GetBody(), W - GUAGE_PIXEL_HALF_OFFSET * 2.0f, H);
}

void HPGaugeHUD::Update(CVector3 position, CQuaternion m_rotation, float Gaugelevel)
{
	CVector3 scale = CVector3::One();
	scale.x = Gaugelevel;
	auto pos = position;
	pos.x += GUAGE_PIXEL_HALF_OFFSET;
	m_sprite.Update(pos, m_rotation, scale, CVector2(0.0f, 0.0f));
	m_waku_sprite.Update(position, m_rotation, CVector3::One(), CVector2(0.0f, 0.0f));
}

void HPGaugeHUD::Draw()
{
	m_sprite.Draw(*g_graphicsEngine->GetD3DDeviceContext());
	m_waku_sprite.Draw(*g_graphicsEngine->GetD3DDeviceContext());
}