#pragma once

class GameLayer : public Layer
{
public:
	CREATE_FUNC(GameLayer);
//	static GameLayer* createGameLayer();
	virtual bool init();
};