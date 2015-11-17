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
	float m_sprScaleRatio = 1; ///# 디폴트값 초기화는 모아서.. 생성자에서 하거나 멤버 선언시 하거나.. 통일되게..
	///# 코딩 컨벤션 m_대or소? 
	bool m_ApplyEffectToMe;
	bool m_ApplyEffectToBullet;

};