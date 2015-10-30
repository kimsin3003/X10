#ifndef __MC_SCENE_H__
#define __MC_SCENE_H__

class MCScene : public cocos2d::CCLayerColor
{
private:
	const float DELTA_TIME = 1.0;
public:
	
	static cocos2d::Scene* createScene();

	virtual bool init();

	void ChangeBackGroundColor(const float time);
	void ChangeToMainScene(Ref* pSender);
	void onMouseUp(Event *event);
	void onMouseDown(Event *event);

	CREATE_FUNC(MCScene);
};


#endif // __MC_Scene_H__
