#pragma once

class Collider;
class Bullet;

class ColliderManager
{
public:
	void Init();
	Bullet* GetBulletToShot();
	Vector<Collider*>& GetColliders(){ return colliders; }

	void AddExplosion(Collider* explosion);
	bool HasBullet();
	void Reset();
	void EraseCollider(Collider* collider);

private:
	void InitColliders(); // called in Init()
	Vector<Collider*> colliders;
	int curBulletIndex;
	int defaultBulletNum;
};