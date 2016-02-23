#ifndef MAINSCENE_H 
#define MAINSCENE_H

class MainScene : public LayerColor
{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(MainScene);

	void PlayAd();

private:
	void ChangeToStageScene();
	void ChangeToMapEditScene();
	void ExitGame();
	void SetToIntro();
	void SetToEnding();
	void TurnOffDisplayStat();
	void WalkToStreetLight();
	void StreetLightOn();
	void StreetLightOff();
	void BlinkStreetLight();
	void BrightenStreetLight();

	Sprite* m_streetLight;
	Sprite* m_character;
	Vec2 m_StreetLightPos;
};

#endif