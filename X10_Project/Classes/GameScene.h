#pragma once

class GameManager;
class GameLayer;
class UILayer;

class GameScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameScene);
	bool init();
	GameLayer* GetGameLayer() { return m_gameLayer; }
	UILayer* GetUILayer() { return m_uiLayer; }
	//Point Getition(){ return m_character->getPosition(); } //sling¿∏∑Œ ø≈±Ë
	void update(float dt);
	void CleanUp();

private:
	Sprite* loadBackground();
	//Sprite* loadCharacter(); //sling¿∏∑Œ ø≈±Ë
	Sprite* m_character;
	Sprite* m_background;

	GameLayer* m_gameLayer;
	UILayer* m_uiLayer;
	GameManager* m_gameManager;
};