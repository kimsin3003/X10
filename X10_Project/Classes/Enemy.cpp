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

	int frameCut = DESTRUCT_FRAMES;
	float frameTime = 0.1f;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(frameCut);

	for (int i = 0; i < frameCut; i++)
	{
		string frameNum = to_string(i + 1);
		string aniFileName = FileStuff::ENEMY_DESTRUCT_ANI + frameNum + ".png";
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(aniFileName);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, frameTime);
	m_destructAnimation = Animate::create(animation);
	m_destructAnimation->retain();

	return true;
}

void Enemy::ToBullet(Bullet* bullet)
{

}

void Enemy::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;

		m_spr->runAction(m_destructAnimation);

		Sequence* removeAfterAnimation = Sequence::create(
			DelayTime::create(DESTRUCT_FRAMES*0.1f),
			CallFunc::create(CC_CALLBACK_0(Enemy::EraseOn, this)),
			NULL);

		m_spr->runAction(removeAfterAnimation);
	}
}

void Enemy::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
}
