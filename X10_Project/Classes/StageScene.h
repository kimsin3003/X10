#pragma once

class LightManager;

class StageScene : public LayerColor
{
public:
	static Scene* createScene();
	CREATE_FUNC(StageScene);
	virtual bool init();
	static void GotoStage(Ref* pSender,int stageNum);
	MenuItemImage* MoveCharacter(MenuItemImage* character, int stageNum);
	static bool m_hasCharacterMoved;

private:
	void SetupCharacter();
	void ChangeToMainScene(Ref* pSender);
	void ChangeToStageScene(Ref* pSender);

	void IntroEvent(float dt);
	void PrintIntroText(const string& message, const Vec2& pos, float startTime, float textScale);
	
	void EndingEvent(float dt);
	void ShowWhiteScene();
	void ShowDeadbody();
	void ShowCrashingScene();
	void ShowBlinkingGaro();
	void ShowAfterCrash();
	void ShowHospital();
	Sprite* LoadBackground();
	Sprite* LoadCharacter();
	void ChangeBackgroundImg(string bgImg);
	void ChangeSoundEffect(const char* sound);
	Point GetCharacterPosition(int stage);
	void SetupLight();
	MenuItemImage* MakeBackButton();
	void GaroOn();
	void GaroOff();

	LightManager* m_lightManager;

	Sprite* m_background;
	int m_maxStageNum;
	int m_stageToPlay;
};