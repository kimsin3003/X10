#pragma once

class Bubble : public Target
{
public:
	CREATE_FUNC(Bubble);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

private:
	enum
	{
		POP_FRAMES = 10
	};
	
	Animate* m_animate;
};