#pragma once

class Bullet;
class Explosion;
class Collider;

class Target : public Node
{
public:
	virtual bool init();
	virtual bool IsEnemy() { return false; }
	void ApplyCollisionEffect(Collider* collider);
	virtual const Rect GetBoundingArea();
	void SetSprScaleRatio(float ratio) { m_sprScaleRatio = ratio; }
	void SetSprScale() { m_spr->setScale(m_sprScaleRatio); }
	bool ToBeErased() { return m_toBeErased; }
	bool IsApplyable() const { return m_applyEffectToMe; };

protected:
	virtual void ToBullet(Bullet* bullet) = 0;
	virtual void ToSelf(const Bullet* bullet) = 0;
	virtual void ToSelf(const Explosion* explosion) = 0;	
	void EraseOn() { m_toBeErased = true; } //for call back
	
	Sprite* m_spr;

	float m_sprScaleRatio;

	bool m_toBeErased;
	bool m_applyEffectToMe;
	bool m_applyEffectToBullet;
};