#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void ChangeSceneToMC(Ref* pSender);
	void ChangeSceneToTW(Ref* pSender);
	void ChangeSceneToJW(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};

#endif // __MainScene_SCENE_H__
