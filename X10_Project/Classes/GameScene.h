#ifndef GAMESCENE_H
#define GAMESCENE_H

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
	void update(float dt);

private:
	Sprite* LoadBackground();

	Sprite* m_background;
	GameLayer* m_gameLayer;
	UILayer* m_uiLayer;
	GameManager* m_gameManager;
};

#endif