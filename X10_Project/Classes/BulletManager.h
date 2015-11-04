#pragma once

class Bullet;

class BulletManager
{
public:
	static BulletManager* GetInstance();
	vector<Bullet*>* GetFlyingBullets();
	Bullet* GetCurrentBullet();

private:
	static BulletManager* instance;
	vector<Bullet*> bullets;
	int CurBulletIndex;
	BulletManager(){};
	~BulletManager(){};
};

