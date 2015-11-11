#pragma once
#include "GameLayer.h"
#include "UILayer.h"

class GameScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init(); 
	CREATE_FUNC(GameScene);
	virtual void update(float dt);
	GameLayer* GetGameLayer() { return gameLayer; }
	UILayer* GetUILayer() { return uiLayer; }

private:
	GameLayer* gameLayer;
	UILayer* uiLayer;

	Sprite* loadBackGround(); //배경그림 만드는 부분.
	const char* BOTTOM_BGIMG_FILE = "res/x10bg.jpg";
};