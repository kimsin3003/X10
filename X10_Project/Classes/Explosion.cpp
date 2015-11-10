#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"
#include "ColliderManager.h"

//Base Class of All Explosions
bool Explosion::init()
{
	isFlying = true;
	particle = ParticleExplosion::create();
	particle->setVisible(true);
	this->addChild(particle);
	lifeTime = 2 * Director::getInstance()->getFrameRate();
	return true;
}

void Explosion::Act()
{
	if (lifeTime > 0){
		lifeTime--;
	}
	else{

		particle->setVisible(false);
		isFlying = false;
		removeFromParent();
		Vector<Collider*> list = ColliderManager::GetInstance()->GetColliders(); 
		///# 으악! 벡터를 통짜로 (복사) 리턴해서 임시 변수에 담아서 쓰고 버리다니..
		// C++의 장점을 다 까먹는 행동...
		list.eraseObject(this);
	}
}

bool Explosion::IsFlying()
{
	return isFlying;
}

void Explosion::SetFlying(bool flag)
{
	isFlying = flag;
}

bool Explosion::IsBullet()
{
	return false;
}

