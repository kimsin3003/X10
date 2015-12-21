#pragma once

class Gull : public Target
{
public:
	CREATE_FUNC(Gull);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

private:
	void Respawn();
	Sprite* m_feather;

	enum 
	{
		BIRD_WIDTH = 100
	};
};