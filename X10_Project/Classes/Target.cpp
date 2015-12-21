#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Target.h"

bool Target::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_applyEffectToMe = true;
	m_applyEffectToBullet = true;
	m_toBeErased = false;
	return true;
}

void Target::ApplyCollisionEffect(Collider* collider)
{
	if (collider->IsBullet())
	{
		ToBullet(static_cast<Bullet*>(collider));
		ToSelf(static_cast<Bullet*>(collider));
	}
	else
	{
		ToSelf(static_cast<Explosion*>(collider));
	}
}

const Rect Target::GetBoundingArea()
{ 
	//Vector<Rect> areas;
	Point nodePos = getPosition();
	Size sprSize = m_spr->getContentSize() * m_sprScaleRatio;
	nodePos.x -= sprSize.width / 2;
	nodePos.y -= sprSize.height / 2;
	//areas.pushBack();
	return Rect(nodePos, sprSize);
}