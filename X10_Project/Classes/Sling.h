#ifndef __SLING_H__
#define __SLING_H__

#include "Bullet.h"

class Sling : public Node
{
public:
	static Sling* createSling();
	CREATE_FUNC(Sling);
	virtual bool init();

	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	
	bool IsShooted() { return isShooted; }
	bool isShooted; ///# 퍼블릭으로 놓을거면 굳이 위의 접근자를 만들 필요 있나? private로 옮기고 멤버 변수 표시를 하는 것이 좋을듯.

	bool IsPressed() { return isPressed; }
	bool isPressed;

	Point posStartClick;
	
	Sprite* Stick; ///# 코딩 컨벤션 및 기본값 초기화 꼭.
	Sprite* Shooter;

	Point angle;
	float power;

	enum { ShooterUIBoundaryHeight = 200,  ///# 코딩 컨벤션: 중괄호 깔맞춤
		ShooterUIBoundaryLeft = 0, 
		ShooterUIBoundaryRight = 400 };
};

#endif