#pragma once

class Bullet;

class BulletManager
{
public:
	static BulletManager* GetInstance();
	void initBulletManager();
	void initBullets();
//	vector<Bullet*> GetFlyingBullets(); //Let's just check bullets state 'isFlying' in game manager
	Bullet* GetBulletToShot();

private:
	static BulletManager* instance;
	vector<Bullet*> bullets;
	int CurBulletIndex;
	int defaultBulletNum;
	BulletManager();
	~BulletManager();
};