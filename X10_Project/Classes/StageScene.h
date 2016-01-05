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
	static bool m_justCleared;

private:
	void SetupCharacter();
	void ChangeToMainScene(Ref* pSender);
	void ChangeToStageScene(Ref* pSender);

	void IntroEvent(float dt);
	
	void EndingEvent(float dt);
	void ChangeToEndingScene();
	void ShowDeadbody();
	void ShowBlinkingLight();
	Sprite* LoadBackground();
	void SetBGM();
	//Sprite* LoadCharacter();
	Point GetCharacterPosition(int stage);
	void SetupLight();
	MenuItemImage* MakeBackButton();
	void SetStreetLight(int isOn);


	LightManager* m_lightManager;
	Sprite* m_background;
	int m_maxStageNum;
	int m_stageToPlay;
};