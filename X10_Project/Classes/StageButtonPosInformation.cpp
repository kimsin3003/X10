#include "stdafx.h"
#include "StageButtonPosInformation.h"
#include "StageInformation.h"

StageButtonPosInformation::StageButtonPosInformation()
{
	m_stageButtonInformation.reserve(StageInformation::GetMaxStageNum());
	SetStageButtonPosInformation();
}

const Vec2 StageButtonPosInformation::GetStageButtonPos(int stageNum)
{
	if (stageNum <= 0 || stageNum > StageInformation::GetMaxStageNum())
	{
		return Vec2(0, 0);
	}

	return m_stageButtonInformation.at(stageNum);
}

void StageButtonPosInformation::SetStageButtonPosInformation()
{
	m_stageButtonInformation.push_back(Vec2(0, 0)); //dummy
	m_stageButtonInformation.push_back(Vec2(49, 347)); //stage 1 - shoes
	m_stageButtonInformation.push_back(Vec2(60, 331));
	m_stageButtonInformation.push_back(Vec2(72, 307)); // stage 3 - weather - rain
	m_stageButtonInformation.push_back(Vec2(90, 295)); //stage 4 - scarf
	m_stageButtonInformation.push_back(Vec2(98, 314));
	m_stageButtonInformation.push_back(Vec2(116, 337));
	m_stageButtonInformation.push_back(Vec2(122, 358)); // stage 7 - weather - rain
	m_stageButtonInformation.push_back(Vec2(129, 376)); //stage 8 - bottle
	m_stageButtonInformation.push_back(Vec2(152, 374));
	m_stageButtonInformation.push_back(Vec2(160, 357)); // stage 10 - weather - rain
	m_stageButtonInformation.push_back(Vec2(190, 346)); // stage 11 - monitor
	m_stageButtonInformation.push_back(Vec2(190, 371));
	m_stageButtonInformation.push_back(Vec2(183, 392)); // stage 13 weather - rain
	m_stageButtonInformation.push_back(Vec2(185, 416)); // stage 14 - letter
	m_stageButtonInformation.push_back(Vec2(205, 405));
	m_stageButtonInformation.push_back(Vec2(222, 393)); // stage 16 weather - snow
	m_stageButtonInformation.push_back(Vec2(236, 392)); //stage 17
}

/*
no	x	y	etc
1	49	347	Shoes
2	60	331	g
3	72	307	g
4	90	295	Scarf
5	98	314	g
6	116	337	g
7	122	358	g
8	129	376	Bottle
9	152	374	g
10	160	357	g
11	190	346	Monitor
12	190	371	g
13	183	392	g
14	185	416	Letter
15	205	405	g
16	222	393	snowing
17	236	392	END
*/