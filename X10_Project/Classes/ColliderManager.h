#pragma once
#include "Collider.h"
class StageInformation;
class Bullet;
class Sling;

class ColliderManager
{
public:
	~ColliderManager() { m_colliders.clear(); }
	
	void InitBullets(StageInformation* si);
	void ResetBullets();
	Bullet* GetBulletToShot(Sling* sling);

	bool HasBulletToShot();
	void AddExplosion(Collider* explosion);
	void EraseDeadColliders(); 
	bool HasCollider();
private:
	Vector<Collider*> m_colliders;
	int m_curBulletIndex;
	int m_BulletNum;

	friend class GameManager;
};