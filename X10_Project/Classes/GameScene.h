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
	Point GetCharacterPosition(){ return m_character->getPosition(); }
	void update(float dt);
	void CleanUp();

private:
	Sprite* loadBackground();
	Sprite* loadCharacter();
	Sprite* m_character;
	Sprite* m_background;

	GameLayer* m_gameLayer;
	UILayer* m_uiLayer;
	GameManager* m_gameManager;
};