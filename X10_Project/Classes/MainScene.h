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
	void SetDisplayStat(bool isOn);
	void StreetLightOn();
	void StreetLightOff();
	void BlinkStreetLight();
	void TurnStreetLight();

	void ChangeToMapEditScene(Ref* pSender);

	void SetToIntro();
	void SetToEnding();

	Sprite* m_StreetLight;
	Sprite* m_character;
	Vec2 m_StreetLightPos;
};
