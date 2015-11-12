#pragma once
class StageInformation;
class Collider;
class Bullet;
class Sling;

class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();
	
	void InitBullets(StageInformation* si);

	Bullet* GetBulletToShot(Sling* sling);
	Vector<Collider*>& GetColliders(){ return colliders; }

	bool HasBullet();
	void AddExplosion(Collider* explosion);
	void EraseCollider(Collider* collider); 

private:
	Vector<Collider*> colliders;
	int curBulletIndex;
	int defaultBulletNum;
};