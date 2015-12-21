#pragma once

class Stone : public Target
{
public:
	CREATE_FUNC(Stone);
	bool init();

	enum 
	{
		DESTRUCT_FRAMES = 9
	};
protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);
};