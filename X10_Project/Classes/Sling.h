#ifndef __SLING_H__
#define __SLING_H__

class Sling : public cocos2d::Layer
{
public:
	Sling();
	void Shot();


	Sprite* Stick;
	Sprite* Shooter;
	float angle;
	float power;
};

#endif