#pragma once

class Collider;
class Bullet;
class Explosion;

class Target : public Node
{
public:
	virtual bool init();
	void ApplyCollisionEffect(Collider* collider); //재정의 ㄴㄴ 안에 부르는 To~~~들만 구현하면 되도록 
	const Rect& GetBoundingArea() { return Rect(getPosition(), spr->getContentSize()); }

protected:
	Sprite* spr;

	virtual void ToBullet(Bullet* collider) = 0;
	virtual void ToExplosion(Explosion* explosion) = 0;
	virtual void ToSelf(const Bullet* bullet) = 0;
	virtual void ToSelf(const Explosion* explosion) = 0;

	const float TARGET_WIDTH = 5;
	const float TARGET_HEIGHT = 5;
};