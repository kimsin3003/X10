#ifndef __MC_SCENE_H__
#define __MC_SCENE_H__

class MCScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void ChangeToMainScene(Ref* pSender);

	CREATE_FUNC(MCScene);
};

#endif // __MC_Scene_H__
