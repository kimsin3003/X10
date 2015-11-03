#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "Target.h"
#include "Sling.h"

class GameScene : public cocos2d::LayerColor
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();
	static cocos2d::Scene* createScene();
	
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	bool isPressed = false;
	void bulletBoom(Node* sender, void* pos);
	void ChangeToMainScene(Ref* pSender);

	void update(float dt);
	Target* CheckHit();
	void HitOperator(Target* target);

	Bullet* bullet;
	Sling* sling;
	vector<Target*> targetList;

	Layer* bulletLayer;
};

#endif