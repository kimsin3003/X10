#ifndef __TW_SCENE_H__
#define __TW_SCENE_H__

class TWScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void ChangeToMainScene(Ref* pSender);

	CREATE_FUNC(TWScene);
};

#endif // __TW_Scene_H__
