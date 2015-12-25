#include "stdafx.h"
#include "Target.h"
#include "Stone.h"
#include "FileStuff.h"
#include "Bullet.h"
#include <SimpleAudioEngine.h>

bool Stone::init()
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

void Stone::ToBullet(Bullet* bullet)
{
	if (m_applyEffectToBullet)
	{
		bullet->Crashed();
		m_applyEffectToBullet = false;
	}
}

void Stone::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		float scale = m_spr->getScale();
		m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::STAR_HAPPY);
		addChild(m_spr);
		m_spr->setScale(scale);
		m_applyEffectToMe = false;

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileStuff::STONE_BREAK_SOUND, false, 1, 0, 1);

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
			CallFunc::create(CC_CALLBACK_0(Stone::EraseOn, this)),
			NULL);

		m_spr->runAction(action);
	}
}

void Stone::ToSelf(const Explosion* explosion)
{

}
