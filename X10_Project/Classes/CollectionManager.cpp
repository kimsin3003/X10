#include "stdafx.h"
#include "CollectionManager.h"
#include "Collection.h"
#include "FileStuff.h"
#include "StageScene.h"

CollectionManager::CollectionManager()
{
	m_curColNum = 0;
	m_collections.reserve(5);
}

//Stack 구조로 저장
void CollectionManager::InitCollections(int stageNumber)
{
	switch (stageNumber)
	{
		case MONITOR:
		{
			Collection* monitor = Collection::create();
			monitor->SetSprite(FileStuff::MONITOR, Point(POS_MONITOR::X, POS_MONITOR::Y));
			m_collections.pushBack(monitor);
			m_curColNum++;
		}
		case BOTTLE:
		{
			Collection* bottle = Collection::create();
			bottle->SetSprite(FileStuff::BOTTLE, Point(POS_BOTTLE::X, POS_BOTTLE::Y));
			m_collections.pushBack(bottle);
			m_curColNum++;
		}
		case SCARF:
		{
			Collection* scarf = Collection::create();
			scarf->SetSprite(FileStuff::SCARF, Point(POS_SCARF::X, POS_SCARF::Y));
			m_collections.pushBack(scarf);
			m_curColNum++;
		}
		case SHOES:
		{
			Collection* shoes = Collection::create();
			shoes->SetSprite(FileStuff::SHOES, Point(POS_SHOES::X, POS_SHOES::Y));
			m_collections.pushBack(shoes);
			m_curColNum++;
		}
		case LETTER:
		{
			Collection* letter = Collection::create();
			letter->SetSprite(FileStuff::LETTER, Point(POS_LETTER::X, POS_LETTER::Y));
			m_collections.pushBack(letter);
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
	for (int i = 0; i < m_curColNum; i++)
	{
		layer->addChild(m_collections.at(i));
	}
}