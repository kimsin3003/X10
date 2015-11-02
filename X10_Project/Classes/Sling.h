#ifndef __SLING_H__
#define __SLING_H__

#include "Bullet.h"

class Sling : public Node
{
public:
	static Sling* createSling(Bullet* bullet);
	

	virtual bool init();
	CREATE_FUNC(Sling);

	//mouse listener
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	bool IsShooted() { return isShooted; }

	bool isPressed;

	Point posStartClick;
	Sprite* Stick;
	Sprite* Shooter;

	Point angle; // 0~180
	float power;

	enum { ShooterUIBoundary = 100 };

	bool isShooted;
};

#endif