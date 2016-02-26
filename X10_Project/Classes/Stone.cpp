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

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FileStuff::SOUND_STONE_BREAK);

	m_spr = Sprite::create(FileStuff::BRICK);
	addChild(m_spr);

	int frameCut = DESTRUCT_FRAMES;
	float frameTime = 0.025f;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(frameCut);

	for (int i = 0; i < frameCut; i++)
	{
		string frameNum = to_string(i + 1);
		string aniFileName = FileStuff::BRICK_DESTRUCT_ANI + frameNum + ".png";

		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(aniFileName);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, frameTime);
	m_animate = Animate::create(animation);
	m_animate->retain();

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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
			FileStuff::SOUND_STONE_BREAK);

		m_spr->runAction(m_animate);

		Sequence* removeAfterAnimation = Sequence::create(
			DelayTime::create(DESTRUCT_FRAMES * 0.025f),
			CallFunc::create(CC_CALLBACK_0(Stone::EraseOn, this)),
			NULL);

		m_spr->runAction(removeAfterAnimation);

		m_applyEffectToMe = false;
	}
}

void Stone::ToSelf(const Explosion* explosion)
{

}