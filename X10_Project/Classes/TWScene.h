#ifndef __TW_SCENE_H__
#define __TW_SCENE_H__
using namespace cocos2d;

class TWScene : public LayerColor
{
public:
	static Scene* createScene();

	virtual bool init();

	void ChangeToMainScene(Ref* pSender);
	void onMouseUP(Event* event);
	CREATE_FUNC(TWScene);
	void ChangeBackground(float deltaTIme);
};

#endif // __TW_Scene_H__
