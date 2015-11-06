#pragma once

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void ChangeToMCScene(Ref* pSender);

    void menuCloseCallback(cocos2d::Ref* pSender);
	
    CREATE_FUNC(MainScene);
};
