#pragma once

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	
    void menuCloseCallback(cocos2d::Ref* pSender);
	
    CREATE_FUNC(MainScene);

private:
	void ChangeToStageScene(Ref* pSender);
	void ChangeToStageSceneEffect(Ref* pSender);
	void ShowGaro();
	
	void ChangeToMapEditScene(Ref* pSender);

	void ChangeToJWScene(Ref* pSender);
	void ChangeToMCScene(Ref* pSender);
	void ChangeToTWScene(Ref* pSender);

	Sprite* m_garo;
	Sprite* m_character;
	Vec2 m_garoPos;
};
