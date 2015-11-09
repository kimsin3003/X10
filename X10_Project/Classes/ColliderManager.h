#pragma once

class Collider;

class ColliderManager
{
public:
	static ColliderManager* GetInstance();
	void Init();
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