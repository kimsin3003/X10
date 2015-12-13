#include "stdafx.h"
#include "Collection.h"
#include "CollectionManager.h"
#include "FileStuff.h"

bool Collection::m_isLooking = false;

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
	m_collection->setCallback(CC_CALLBACK_0(Collection::MakeTextBox, this, name, code));

	m_collection->setPosition(pos);
	m_collection->setScale(1.5f);
}

void Collection::MakeTextBox(const string& name, int code)
{
	if (!m_isLooking)
	{
		m_isLooking = true;

		m_textBox = Sprite::create(FileStuff::TEXT_BOX);
		m_textBox->setPosition(160, 240);
		m_textBox->setAnchorPoint(Vec2(0.5f, 0.5f));
		addChild(m_textBox);

		m_collSpr = Sprite::create(name);
		m_collSpr->setPosition(32, 30);
		m_collSpr->setScale(1.5f);
		m_textBox->addChild(m_collSpr);

		m_text = Label::create("", FileStuff::FONT_ARIAL, 10.5f);
		m_text->setAnchorPoint(Vec2(0, 0));
		m_text->setPosition(Vec2(TEXT_POS, 0));
		switch (code)
		{
		case CollectionManager::LETTER:
			LetterExplanation();
			break;
		case CollectionManager::MONITOR:
			MonitorExplanation();
			break;
		case CollectionManager::BOTTLE:
			BottleExplanation();
			break;
		case CollectionManager::SCARF:
			ScarfExplanation();
			break;
		case CollectionManager::SHOES:
			ShoesExplanation();
			break;
		}
		m_collSpr->addChild(m_text);

		CallFuncN* callFuncN = CallFuncN::create(CC_CALLBACK_0(
			Collection::EndLooking, this));

		Spawn* spawn = Spawn::create(
			FadeOut::create(0.5f),
			MoveBy::create(0.5f, Point(0, -15)),
			nullptr);

		Sequence* sequence = Sequence::create(
			DelayTime::create(1.5f), 
			spawn, 
			callFuncN, 
			RemoveSelf::create(true), 
			nullptr);

		Sequence* seq_00 = Sequence::create(
			DelayTime::create(1.5f),
			FadeOut::create(0.475f),
			nullptr);

		Sequence* seq_01 = Sequence::create(
			DelayTime::create(1.5f),
			FadeOut::create(0.475f),
			nullptr);

		m_collSpr->runAction(seq_00);	
		m_text->runAction(seq_01);
		m_textBox->runAction(sequence);
	}
}

void Collection::LetterExplanation()
{
	m_text->setString("Faded away I can't read it");
}

void Collection::MonitorExplanation()
{
	m_text->setString("weird heart beating sound");
}

void Collection::BottleExplanation()
{
	m_text->setString("It hits my neck");
}

void Collection::ScarfExplanation()
{
	m_text->setString("Looks warm");
}

void Collection::ShoesExplanation()
{
	m_text->setString("Small and cute");
}