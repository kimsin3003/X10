#pragma once

class LightManager;

class StageScene : public LayerColor
{
public:
	static Scene* createScene();
	CREATE_FUNC(StageScene);
	virtual bool init();

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
	Point GetCharacterPosition(int stage);
	void SetupLight();
	MenuItemImage* MakeBackButton();
	void SetStreetLight(int isOn);

	void ChangeCharacterToButton(Point finalPos, float scale);
	void PlaySound(const char* file);
	static void GotoStage(Ref* pSender, int stageNum);
	void MoveCharacter(Sprite* character, int stageNum);
	static bool m_justCleared;

	LightManager* m_lightManager;
	Sprite* m_background;
	int m_maxStageNum;
	int m_stageToPlay;
};