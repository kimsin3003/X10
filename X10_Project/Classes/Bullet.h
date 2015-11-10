#pragma once

#include "Collider.h"
#include "Explosion.h"

class Bullet : public Collider
{
public:
	///# 나중에 따로 init을 부르더라도 기본 생성자에서 멤버 초기화는 반드시 하도록. 나중에 초기화가 되기 전에 죽었을때 그걸 확인할 길이 없기 때문...

	CREATE_FUNC(Bullet);

	virtual bool init() override;
	virtual void Act() override;
	void Move(); // called each frame 
	bool IsFlying();
	bool IsExplosing();
	virtual Explosion* GetExplosion();

	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);
	void SetExplosing(bool flag);

	void SetFlying(bool flag);
	bool IsAlive() override;
	bool IsBullet() override;
	void SetAlive(bool flag);

protected:
	void DecreaseLife(); // called in Move()

	///# 코딩컨벤션: 지난주 코멘트중에 멤버 변수와 일반 변수를 구분하도록 하라고 했는데..
	Sprite* spr;
	Vec2 direction;
	float speed;
	float lifeTime;

	float speedSetRatio;
	float speedDecreaseRatio;
	float timeDecrease;

private:
	Sprite* MakeBody();

	///# 이런 상수들은 클래스 전용일 경우 enum으로 빼고, 시스템 전역일 경우 config.h 같은데 모아놓도록.
	const int DEFAULT_FRAMES = 5;
	const float DEFAULT_WIDTH = 20;
	const float DEFAULT_HEIGHT = 20;
	const float DEFAULT_RATIO = 2;
	bool isExplosing;
};