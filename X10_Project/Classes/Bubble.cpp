#include "stdafx.h"
#include "Target.h"
#include "Bubble.h"
#include "FileStuff.h"
#include <SimpleAudioEngine.h>

bool Bubble::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::BUBBLE);
	addChild(m_spr);

	return true;
}

void Bubble::ToBullet(Bullet* bullet)
{

}

void Bubble::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileStuff::SOUND_BUBBLE_POP, false, 1.0f, 0, 0);
		m_applyEffectToMe = false;

		// before pop sprite
		/*m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::BUBBLE_POP);
		m_spr->setScale(m_sprScaleRatio);
		addChild(m_spr);
		*/

		int frameCut = POP_FRAMES;
		float frameTime = Director::getInstance()->getSecondsPerFrame()*10.0;

		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(frameCut);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/target/x10.plist");

		for (int i = 0; i < frameCut; i++)
		{
			string stageNum = to_string(frameCut - i); // from 10 -> to 1
			string aniFileName = FileStuff::BUBBLE_POP_ANI + stageNum + ".png";
			
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(aniFileName);
			animFrames.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, frameTime);
		Animate* animate = Animate::create(animation);
		m_spr->runAction(animate);

		//remove self
		Sequence* action = Sequence::create(
			DelayTime::create(frameTime*frameCut),
			CallFunc::create(CC_CALLBACK_0(Bubble::EraseOn, this)),
			NULL);

		m_spr->runAction(action);
	}
}

void Bubble::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
}