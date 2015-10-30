#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"


class Bullet : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	void Start(Vec2 initialDirection);
	Sprite* GetInstance();

	int GetSpeed(){ return speed; }
	void SetSpeed(int _speed){ speed = _speed; }

	CREATE_FUNC(Bullet);
	void UpdateState();
	bool IsAlive(){ return alive; }
	bool HitCheck();
private:

	Sprite* bullet;
	Vec2 direction;
	int speed;
	bool alive;
};

#endif