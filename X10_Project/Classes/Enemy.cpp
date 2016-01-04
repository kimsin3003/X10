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
		m_applyEffectToMe = false;
		float scale = m_spr->getScale();
		m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::ENEMY);
		addChild(m_spr);
		m_spr->setScale(scale);

		int frameCut = DESTRUCT_FRAMES;
		float frameTime = 0.1f;

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
