#pragma once
class Class_of_NewGO;
class Game:public GameObject
{
public:
	Game(int No, char* obj_name);
	~Game();
	bool Start();
	void Update();
	void Draw();
	void UIDraw();								//UI‚Æ‚©‚Ì•`‰æ
private:
	enum gamestate {
		start,
		stop,
		end
	};
	gamestate state = end;


	Class_of_NewGO *newObject = nullptr;
	ShaderResourceView shaderResource;
	ShaderResourceView startshaderResource;
	ShaderResourceView OnGameshaderResource;
	sprite m_sprite;
	sprite m_startSprite;
	sprite OnGameSprite;
	ShadowMap shadowMap;
};

