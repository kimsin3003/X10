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

	///# 마찬가지
	const string FILE_SEEBIRD = "res/target/SeeBird.png";
	const string FILE_FEATHER = "res/target/Feather.png";

	enum 
	{
		BIRD_WIDTH = 100
	};
};