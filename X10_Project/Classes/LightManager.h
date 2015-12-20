#pragma once

#include "cocos2d/cocos/math/Vec2.h"

class LightManager
{
public:
	LightManager();
	Sprite* GetLight(int stageNum);

private:
	void SetLights();
	void InitPositions();
	Sprite* MakeLight(string fileDir, int idx);
	Vector<Sprite*> m_lights;
	vector<Vec2> m_positions;
};