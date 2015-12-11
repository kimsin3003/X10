#pragma once

#include "cocos2d/cocos/math/Vec2.h"

class StageButtonPosInformation
{
public:
	StageButtonPosInformation();
	const Vec2 GetStageButtonPos(int stageNum);

private:
	void SetStageButtonPosInformation();
	vector<Vec2> m_stageButtonInformation;
};