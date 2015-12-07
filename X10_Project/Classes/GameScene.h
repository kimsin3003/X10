#pragma once

class GameManager;
class GameLayer;
class UILayer;

class GameScene : public Layer
{
public:
	GameScene();
	static Scene* createScene();
	virtual bool init(); 
	CREATE_FUNC(GameScene);
	virtual void update(float dt);
	GameLayer* GetGameLayer() { return gameLayer; }
	UILayer* GetUILayer() { return uiLayer; }

private:
	GameLayer* gameLayer;
	UILayer* uiLayer;
	GameManager* gameManager;
	Sprite* loadBackground(); //배경그림 만드는 부분.
	const char* BOTTOM_BGIMG_FILE = "res/background2.png"; ///# 기술부채
	const char* CHARACTER_FILE = "res/character2.png";
};