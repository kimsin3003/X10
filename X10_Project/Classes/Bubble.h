#pragma once

class Bubble : public Target
{
public:
	CREATE_FUNC(Bubble);
	bool init();

protected:
	void ToBullet(Bullet* bullet); ///# 쓰지도 않는 인자를 인터페이스때문에 이렇게 두는 것은 구조적인 문제가 있는것이라 볼 수 있다.
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

private:
};