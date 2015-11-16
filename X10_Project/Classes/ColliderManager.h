#pragma once
#include "Collider.h"
class StageInformation;
class Bullet;
class Sling;

class ColliderManager
{
public:
	ColliderManager() {}
	~ColliderManager() {}
	
	void InitBullets(StageInformation* si);
	void ResetBullets();
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