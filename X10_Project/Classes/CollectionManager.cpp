#include "stdafx.h"
#include "StageInformation.h"
#include "CollectionManager.h"
#include "Collection.h"
#include "FileStuff.h"
#include "StageScene.h"

CollectionManager::CollectionManager()
{
	m_curColNum = 0;
	m_collections.reserve(5);
	m_colPos = Point(40, 75);
	m_deltaPos = Point(30, 0);
}

void CollectionManager::InitCollections(int stageNumber)
{
	int maxStageNum = StageInformation::GetMaxStageNum();
	if (stageNumber > maxStageNum)
	{
		stageNumber = LETTER;
	}

	switch (stageNumber)
	{
		case LETTER:
		case LETTER + 1:
		case LETTER + 2:
		case LETTER + 3: //14~17 //*last stage -> don't 
						 // instead collections rotating event
		{
			Collection* letter = Collection::create();
			letter->SetCollection(FileStuff::LETTER, m_colPos, LETTER);
			m_collections.pushBack(letter);
			m_curColNum++;
		}
		case MONITOR:
		case MONITOR + 1:
		case MONITOR + 2: //11~13
		{
			Collection* monitor = Collection::create();
			monitor->SetCollection(FileStuff::MONITOR, m_colPos += m_deltaPos, MONITOR);
			m_collections.pushBack(monitor);
			m_curColNum++;
		}
		case BOTTLE:
		case BOTTLE + 1:
		case BOTTLE + 2: //8~10
		{
			Collection* bottle = Collection::create();
			bottle->SetCollection(FileStuff::BOTTLE, m_colPos += m_deltaPos, BOTTLE);
			m_collections.pushBack(bottle);
			m_curColNum++;
		}
		case SCARF:
		case SCARF + 1:
		case SCARF + 2:
		case SCARF + 3:	// 4~7
		{
			Collection* scarf = Collection::create();
			scarf->SetCollection(FileStuff::SCARF, m_colPos += m_deltaPos, SCARF);
			m_collections.pushBack(scarf);
			m_curColNum++;
		}
		case SHOES:
		case SHOES + 1:
		case SHOES + 2: //1~3
		{
			Collection* shoes = Collection::create();
			shoes->SetCollection(FileStuff::SHOES, m_colPos += m_deltaPos, SHOES);
			m_collections.pushBack(shoes);
			m_curColNum++;
		}
	}
}

void CollectionManager::ResetCollections()
{
	for (Collection* collection : m_collections)
	{
		delete collection;
	}
	m_collections.clear();
}

void CollectionManager::AppendCollectionToLayer(StageScene* layer)
{
	Vector<MenuItem*> menuList;

	for (int i = 0; i < m_curColNum; i++)
	{
		menuList.pushBack(m_collections.at(i)->GetCollection());
	}

	Menu* menu = Menu::createWithArray(menuList);
	menu->setPosition(Vec2::ZERO);
	layer->addChild(menu);
}

Sprite* CollectionManager::GetCollectionSprOfStage(int stageNum)
{
	Sprite* collectionSpr;
	string sprToLoad;

	switch (stageNum)
	{
	case MONITOR:
		sprToLoad = FileStuff::MONITOR;
		break;
	case BOTTLE:
		sprToLoad = FileStuff::BOTTLE;
		break;
	case SCARF:
		sprToLoad = FileStuff::SCARF;
		break;
	case SHOES:
		sprToLoad = FileStuff::SHOES;
		break;
	case LETTER:
		sprToLoad = FileStuff::LETTER;
		break;
	default:
		sprToLoad = FileStuff::CLOUD;
	};
	
	collectionSpr = Sprite::create(sprToLoad);

	return  collectionSpr;
}
