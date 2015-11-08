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
};