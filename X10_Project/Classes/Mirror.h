#pragma once

class Mirror : public Target
{
public:
	CREATE_FUNC(Mirror);
	bool init();
	void ApplyCollisionEffect(Collider* collider);

protected:
	void ToBullet(Bullet* collider);
	void ToExplosion(Explosion* explosion);
	void ToSelf(Bullet* bullet);
	void ToSelf(Explosion* explosion);

	const string FILE_MIRROR = "res/Mirror.png";
	const string FILE_MIRROR_ANGRY = "res/MirrorAngry.png";
};