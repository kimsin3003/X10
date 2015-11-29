#pragma once

class Collider;
class Bullet;
class Explosion;
class TargetManager;

class Target : public Node
{
public:
	virtual bool init();
	void ApplyCollisionEffect(Collider* collider);
	const Rect& GetBoundingArea();
	void SetSprScaleRatio(float ratio) { m_sprScaleRatio = ratio; }
	void SetSprScale() { m_spr->setScale(m_sprScaleRatio); }
	bool ToBeErased() { return m_toBeErased; }
	bool IsEnemy() { return m_isEnemy; }

protected:
	virtual void ToBullet(Bullet* bullet) = 0;
	virtual void ToSelf(const Bullet* bullet) = 0;
	virtual void ToSelf(const Explosion* explosion) = 0;	
	void EraseOn() { m_toBeErased = true; }

	Sprite* m_spr;
	float m_sprScaleRatio;
	bool m_isEnemy;
	bool m_toBeErased;
	bool m_applyEffectToMe;
	bool m_applyEffectToBullet;
};