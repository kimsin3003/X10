#pragma once

class SeeBird : public Target
{
public:
	CREATE_FUNC(SeeBird);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

private:
	Sprite* m_feather;

	enum 
	{
		BIRD_WIDTH = 100
	};
};