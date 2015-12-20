#include "stdafx.h"
#include "LightManager.h"
#include "StageInformation.h"

LightManager::LightManager()
{
	InitPositions();
	SetLights();
}

Sprite* LightManager::GetLight(int stageNum)
{
	if (stageNum <= 0 || stageNum > StageInformation::GetMaxStageNum())
	{
		return Sprite::create(FileStuff::ENEMY);
	}

	return m_lights.at(stageNum);
}

void LightManager::SetLights()
{
	m_lights.pushBack(Sprite::create(FileStuff::ENEMY)); //dummy
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_LEGT_01, 1));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_RIGHT_01, 2));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_LEGT_02, 3));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_RIGHT_02, 4));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_LEGT_03, 5));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_RIGHT_03, 6));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_LEGT_04, 7));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_RIGHT_04, 8));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_LEGT_05, 9));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_RIGHT_05, 10));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_LEGT_06, 11));
	m_lights.pushBack(MakeLight(FileStuff::STAGE_LIGHTS_RIGHT_06, 12));
}

void LightManager::InitPositions()
{
	m_positions.push_back(Vec2(0,0)); //dummy
	m_positions.push_back(Vec2(50 + 15, 95 - 10));
	m_positions.push_back(Vec2(222+18, 94 - 7));
	m_positions.push_back(Vec2(60 + 15, 201- 7));
	m_positions.push_back(Vec2(217 + 15, 200 - 5));
	m_positions.push_back(Vec2(86 + 10, 290 - 5));
	m_positions.push_back(Vec2(209 + 13, 290 - 5));
	m_positions.push_back(Vec2(93 + 11, 356));
	m_positions.push_back(Vec2(204 + 10, 357 - 3));
	m_positions.push_back(Vec2(102 + 10, 414-1));
	m_positions.push_back(Vec2(202 + 5, 416 - 3));
	m_positions.push_back(Vec2(110 + 15, 467));
	m_positions.push_back(Vec2(194 + 15, 468));
}

Sprite* LightManager::MakeLight(string fileDir, int idx)
{
	Sprite* spr = Sprite::create(fileDir);
	spr->setPosition(m_positions.at(idx));
	spr->setAnchorPoint(Vec2(0.5, 0.5));
	spr->setScale(1.5f);
	return spr;
}