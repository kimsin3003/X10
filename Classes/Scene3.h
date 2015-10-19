#ifndef __SCENE3_H__
#define __SCENE3_H__

#include "cocos2d.h"

class Scene3 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene3);
};

#endif // __SCENE3_H__
