#ifndef __JW_SCENE_H__
#define __JW_SCENE_H__

class JWScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void ChangeToMainScene(Ref* pSender);

	CREATE_FUNC(JWScene);
};

#endif