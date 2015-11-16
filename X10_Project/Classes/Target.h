#pragma once

class Collider;
class Bullet;
class Explosion;

class Target : public Node
{
public:
	virtual bool init();

	void ApplyCollisionEffect(Collider* collider); //재정의 ㄴㄴ 안에 부르는 To~~~들만 구현하면 되도록 
	const Rect& GetBoundingArea();
	void SetSprScaleRatio(float ratio) { m_sprScaleRatio = ratio; }
	void SetSprScale() { m_spr->setScale(m_sprScaleRatio); }
protected:
	virtual void ToBullet(Bullet* collider) = 0;
	virtual void ToExplosion(Explosion* explosion) = 0;
	virtual void ToSelf(const Bullet* bullet) = 0;
	virtual void ToSelf(const Explosion* explosion) = 0;	
	
	Sprite* m_spr;
	float m_sprScaleRatio = 1;
	bool m_ApplyEffectToMe;
	bool m_ApplyEffectToBullet;

};