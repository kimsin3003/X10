#pragma once

class Bullet;

class BulletManager
{
public:
	static BulletManager* GetInstance();
	void Init();
//	vector<Bullet*> GetFlyingBullets(); //Let's just check bullets state 'isFlying' in game manager
	Bullet* GetBulletToShot();
	vector<Bullet*> GetBullets(){ return bullets; }
	void AddExplosion(Bullet* explosion);

private:
	void InitBullets(); // called in Init()

	static BulletManager* instance;
	vector<Bullet*> bullets;
	int curBulletIndex;
	int defaultBulletNum;
	BulletManager();
	~BulletManager();
};