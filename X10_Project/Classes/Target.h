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
protected:
	virtual void ToBullet(Bullet* collider) = 0;
	virtual void ToSelf(const Bullet* bullet) = 0;
	virtual void ToSelf(const Explosion* explosion) = 0;	
	
	Sprite* m_spr;
	float m_sprScaleRatio = 1;
	bool m_toBeErased;
	bool m_applyEffectToMe;
	bool m_applyEffectToBullet;
};