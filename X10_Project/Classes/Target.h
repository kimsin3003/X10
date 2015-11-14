#pragma once

class Collider;
class Bullet;
class Explosion;

class Target : public Node
{
public:
	virtual bool init();
	void ApplyCollisionEffect(Collider* collider);// 모든 타겟이 이 함수 내부 처리는 같으므로 그대로 쓰는게? 재정의 하지 말고.
	virtual const Rect& GetBoundingArea() = 0;

protected:
	Sprite* spr; //임시로 퍼블릭으로 옮김

	virtual void ToBullet(Bullet* collider) = 0;
	virtual void ToExplosion(Explosion* explosion) = 0;
	virtual void ToSelf(Bullet* bullet) = 0;
	virtual void ToSelf(Explosion* explosion) = 0;

	const float TARGET_WIDTH = 5;
	const float TARGET_HEIGHT = 5;


};