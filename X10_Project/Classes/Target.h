#pragma once

class Collider;
class Bullet;
class Explosion;

class Target : public Node
{
public:
	CREATE_FUNC(Target);
	virtual bool init();
	virtual void ApplyCollisionEffect(Collider* collider);
	virtual const Rect& GetBoundingArea();

protected:
	Sprite* spr; //임시로 퍼블릭으로 옮김

	virtual void ToBullet(Bullet* collider);
	virtual void ToExplosion(Explosion* explosion);
	virtual void ToSelf(Bullet* bullet);
	virtual void ToSelf(Explosion* explosion);


};