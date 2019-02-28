#pragma once
class Effect
{
public:
	Effect();
	~Effect();
	void Init(const wchar_t* filepath);
	void Play(CVector3 position, CVector3 scale);
	void Update();
	void Draw();
	void Release();
private:
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
};

