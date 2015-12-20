#include "stdafx.h"
#include "Target.h"
#include "Star.h"
#include "FileStuff.h"
#include "Bullet.h"

bool Star::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::STAR_SAD);
	addChild(m_spr);
	m_applyEffectToMe = true;
	m_applyEffectToBullet = true;
	return true;
}

void Star::ToBullet(Bullet* bullet)
{
	if (m_applyEffectToBullet)
	{
		bullet->Crashed();
		m_applyEffectToBullet = false;
	}
}

void Star::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::STAR_HAPPY);
		addChild(m_spr);
		m_applyEffectToMe = false;

		int frameCut = DESTRUCT_FRAMES;
		float frameTime = Director::getInstance()->getSecondsPerFrame()*10.0;

		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(frameCut);

		for (int i = 0; i < frameCut; i++)
		{
			string frameNum = to_string(i+1); // from 10 -> to 1
			string aniFileName = FileStuff::BRICK_DESTRUCT_ANI + frameNum + ".png";

			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(aniFileName);
			animFrames.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, frameTime);
		Animate* animate = Animate::create(animation);
		m_spr->runAction(animate);

		//remove self
		Sequence* action = Sequence::create(
			DelayTime::create(frameTime*frameCut),
			CallFunc::create(CC_CALLBACK_0(Star::EraseOn, this)),
			NULL);

		m_spr->runAction(action);
	}
}

void Star::ToSelf(const Explosion* explosion)
{

}
