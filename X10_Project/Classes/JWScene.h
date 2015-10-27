#ifndef __JW_SCENE_H__
#define __JW_SCENE_H__

class JWScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void ChangeToMainScene(Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(JWScene);
};

#endif // __JW_Scene_H__
