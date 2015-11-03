#pragma once
class Bullet;

//if you want to make targets like enemy or some obstacles,  you should extend Target
class Target : public Layer
{
public:
	virtual void SetEffect(Bullet& bullet) = 0;

	virtual bool init() = 0;

	void setPosition(const Vec2 &position) override { mySprite->setPosition(position); } ///# 인라인 함수가 아닌 호출이 있다면 구현부 cpp로 옮기기 바람

	const Vec2& getPosition() const override { return mySprite->getPosition(); }

	void setAnchorPoint(const Vec2& anchorPoint) override { mySprite->setAnchorPoint(anchorPoint); }

	Rect getBoundingBox() const override { return mySprite->getBoundingBox(); } ///# 마찬가지로 구현부로..

protected:
	Sprite* mySprite;
};

