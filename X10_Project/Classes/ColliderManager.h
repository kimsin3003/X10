#pragma once

class Collider;

class ColliderManager
{
public:
	static ColliderManager* GetInstance();
	void Init();
//	Vector<Collider*> GetFlyingColliders(); //Let's just check Colliders state 'isFlying' in game manager
	Collider* GetColliderToShot();
	Vector<Collider*>& GetColliders(){ return colliders; }
	void AddExplosion(Collider* explosion);
	bool HasNextCollider();
	void Reset();

private:
	void InitColliders(); // called in Init()
	static ColliderManager* instance;
	Vector<Collider*> colliders;
	int curColliderIndex;
	int defaultColliderNum;
	ColliderManager();
	~ColliderManager();
};