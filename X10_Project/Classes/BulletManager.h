#pragma once

class Bullet;

class BulletManager
{
public:
	static BulletManager* GetInstance();
	void Init();
//	Vector<Bullet*> GetFlyingBullets(); //Let's just check bullets state 'isFlying' in game manager
	Bullet* GetBulletToShot();
	Vector<Bullet*>& GetBullets(){ return bullets; }
	void AddExplosion(Bullet* explosion);
	bool HasNextBullet();

private:
	void InitBullets(); // called in Init()

	static BulletManager* instance;
	Vector<Bullet*> bullets;
	int curBulletIndex;
	int defaultBulletNum;
	BulletManager();
	~BulletManager();
};