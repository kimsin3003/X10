#pragma once

class Bullet;

class BulletManager //singletone Bullet Manager
{
private:
	vector<Bullet*>bulletList;
	int CurrentBulletIndex;
	static BulletManager* instance;
public:
	
private:
	Bullet* GetNextBullet();
	BulletManager();
	~BulletManager();
public:
	vector<Bullet*> GetFlyingBullets();
	static BulletManager* GetInstance();
};

