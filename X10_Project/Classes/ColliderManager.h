#ifndef COLLIMAN_H 
#define COLLIMAN_H
#include "Collider.h"
class Target;
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
	int m_bulletNum;
	int m_normalNum;
	int m_crossNum;
	friend class GameManager;
};

#endif