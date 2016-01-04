#pragma once

class Stone : public Target
{
public:
	CREATE_FUNC(Stone);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

private:
	enum
	{
		DESTRUCT_FRAMES = 9
	};

	Animate* m_animate;
};