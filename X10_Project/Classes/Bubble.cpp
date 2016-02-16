#include "stdafx.h"
#include "Target.h"
#include "Bubble.h"
#include "FileStuff.h"
#include <SimpleAudioEngine.h>
#include <string>

bool Bubble::init()
{
	if (!Target::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FileStuff::SOUND_BUBBLE_POP);

	m_spr = Sprite::create(FileStuff::BUBBLE);
	addChild(m_spr);

	int frameCut = POP_FRAMES;
	float frameTime = 0.025f;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(frameCut);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/target/x10.plist");
	for (int i = 0; i < frameCut; i++)
	{
		string frameNum = to_string(frameCut - i);
		string aniFileName = FileStuff::BUBBLE_POP_ANI + frameNum + ".png";

		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(aniFileName);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, frameTime);
	m_animate = Animate::create(animation);
	m_animate->retain();

	return true;
}

void Bubble::ToBullet(Bullet* bullet)
{

}

void Bubble::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
			FileStuff::SOUND_BUBBLE_POP, false, 1.0f, 0, 0);

		m_applyEffectToMe = false;

		m_spr->runAction(m_animate);

		Sequence* removeAfterAnimation = Sequence::create(
			DelayTime::create(POP_FRAMES * 0.025f),
			CallFunc::create(CC_CALLBACK_0(Bubble::EraseOn, this)),
			NULL);

		m_spr->runAction(removeAfterAnimation);
	}
}

void Bubble::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
}