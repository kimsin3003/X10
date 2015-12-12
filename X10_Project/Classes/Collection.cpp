#include "stdafx.h"
#include "Collection.h"
#include "CollectionManager.h"
#include "FileStuff.h"

bool Collection::init()
{
	setPosition(Point::ZERO);
	return true;
}

void Collection::SetCollection(const string& name, const Point& pos, int code)
{
	m_collection = MenuItemImage::create();
	Sprite* collectionSpr = Sprite::create(name);
	m_collection->setNormalImage(collectionSpr);
	
	Sprite* collectionSprLarger = Sprite::create(name);
	collectionSprLarger->setScale(1.50f);
	m_collection->setSelectedImage(collectionSprLarger);
	m_collection->getSelectedImage()->setAnchorPoint(Vec2(0.2f, 0.2f));

	switch (code)
	{
	case CollectionManager::LETTER:
		m_collection->setCallback(CC_CALLBACK_0(
			Collection::LetterExplanation, this));
		break;
	case CollectionManager::MONITOR:
		m_collection->setCallback(CC_CALLBACK_0(
			Collection::MonitorExplanation, this));
		break;
	case CollectionManager::BOTTLE:
		m_collection->setCallback(CC_CALLBACK_0(
			Collection::BottleExplanation, this));
		break;
	case CollectionManager::SCARF:
		m_collection->setCallback(CC_CALLBACK_0(
			Collection::ScarfExplanation, this));
		break;
	case CollectionManager::SHOES:
		m_collection->setCallback(CC_CALLBACK_0(
			Collection::ShoesExplanation, this));
		break;
	}

	setPosition(Vec2::ZERO);
	m_collection->setPosition(pos);
	m_collection->setScale(1.5f);
}

void Collection::LetterExplanation()
{

}

void Collection::MonitorExplanation()
{

}

void Collection::BottleExplanation()
{

}

void Collection::ScarfExplanation()
{

}

void Collection::ShoesExplanation()
{

}

