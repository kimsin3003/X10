#include "stdafx.h"
#include "Explosion.h"
#include "Enemy.h"

Explosion* Explosion::createExplosion()
{
	auto Explosion = Explosion::create();
	auto body = Sprite::create("res/explosion.png");
	body->setName("ExplosionBody");
	Explosion->addChild(body);

	return Explosion;
}

bool Explosion::init()
{
	if (Node::init() == false)
		return false;

	this->mainDamage = EXPLOSION_CONST::DEFAULT_DAMAGE;

	return true;
}

void Explosion::boom(const float dTime)
{
	auto body = this->getChildByName("ExplosionBody");
	if (body != nullptr && body->getScale() * body->getContentSize().width < 100)
	{
		makeBigger(body);
	}
	else
	{
		this->removeFromParent();
	}
	return;
}

void Explosion::makeBigger(Node* spr)
{
	spr->setScale(spr->getScale()+0.2);
}

float Explosion::calcDmg(float enemyX, float enemyY, const float distance)
{
	float myX = this->getPositionX();
	float myY = this->getPositionY();
	float deltaX = myX - enemyX;
	float deltaY = myY - enemyY;
	float result = mainDamage / (distance / 10);
	CCLOG("mainDMG : %f, Dmg : %f", mainDamage, result);
	return result;
}

void Explosion::boom(Scene* scene, Point p)
{
	auto boom = Explosion::createExplosion();
	if (boom == nullptr)
		return;
	boom->setName("boom");
	boom->setPosition(p);
	boom->schedule(schedule_selector(Explosion::boom), 0.1);
	scene->addChild(boom);

	Enemy* enemy = (Enemy*)scene->getChildByName("Enemy");
	if (enemy == nullptr)
		return;
	auto enemyLocation = enemy->getPosition();
	float dist = enemyLocation.distance(boom->getPosition());
	CCLOG("Enemy( %f, %f ) , Distance: %f", enemy->getPositionX(), enemy->getPositionY(), dist);
	if (dist < 100){
		if (dist < 2.0)
		{
			auto x10Label = Label::createWithTTF("!!!X10!!!", "fonts/arial.ttf", 100);
			x10Label->setPosition(150, 350);
			auto action = MoveBy::create(1.0, Point(0, 0));
			auto destroyAfterAction = Sequence::create(action, RemoveSelf::create(), NULL);
			x10Label->runAction(destroyAfterAction);
			scene->addChild(x10Label);
		}
		enemy->hitByExplosion(boom, dist);
	}
}