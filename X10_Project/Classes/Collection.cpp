#include "stdafx.h"
#include "Collection.h"

bool Collection::init()
{
	setPosition(Point::ZERO);
	return true;
}

void Collection::SetSprite(const string& name, const Point& pos)
{
	m_spr = Sprite::create(name);
	setPosition(pos);
	m_spr->setPosition(Point::ZERO);
	addChild(m_spr);
}
