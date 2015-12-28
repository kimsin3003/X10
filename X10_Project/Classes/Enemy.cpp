#include "stdafx.h"
#include "Enemy.h"
#include "FileStuff.h"
#include "Bullet.h"
#include <SimpleAudioEngine.h>

bool Enemy::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::ENEMY);
	addChild(m_spr);

	return true;
}

void Enemy::ToBullet(Bullet* bullet)
{

}

void Enemy::ToSelf(const Bullet* bullet)
{
	
	if (m_applyEffectToMe)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileStuff::SOUND_UFO_EXPLODE, false, 1.0f, 0, 0);
		m_applyEffectToMe = false;
		float scale = m_spr->getScale();
		m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::ENEMY);
		addChild(m_spr);
		m_spr->setScale(scale);

		//사운드 추가할 부분
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(???);

		int frameCut = DESTRUCT_FRAMES;
		float frameTime = Director::getInstance()->getSecondsPerFrame()*40.0;

		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(frameCut);

		for (int i = 0; i < frameCut; i++)
		{
			string frameNum = to_string(i + 1); // from 10 -> to 1
			string aniFileName = FileStuff::ENEMY_DESTRUCT_ANI + frameNum + ".png";
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(aniFileName);
			animFrames.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, frameTime);
		Animate* animate = Animate::create(animation);
		m_spr->runAction(animate);

		//remove self
		Sequence* action = Sequence::create(
			DelayTime::create(frameTime*frameCut),
			CallFunc::create(CC_CALLBACK_0(Enemy::EraseOn, this)),
			NULL);
		m_spr->runAction(action);
	}
}

void Enemy::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
}
