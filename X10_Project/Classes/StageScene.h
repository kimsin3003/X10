#pragma once

class LightManager;

class StageScene : public LayerColor
{
public:
	static Scene* createScene();
	CREATE_FUNC(StageScene);
	virtual bool init();
	static void GotoStage(Ref* pSender,int stageNum);
	void MoveCharacter(Ref* character, int stageNum);
	static bool m_hasCharacterMoved;

private:
	void SetupCharacter();
	void ChangeToMainScene(Ref* pSender);
	void ChangeToStageScene(Ref* pSender);

	void IntroEvent(float dt);
	void PrintIntroText(const string& message, const Vec2 pos, float startTime, float keepTime);
	
	void EndingEvent(float dt);
	void ShowLastLight();
	void ShowDeadBody();
	void ShowCrashingScene();

	Sprite* LoadBackground();
	Sprite* LoadCharacter();
	Point GetCharacterPosition(int stage);
	void SetupLight();
	MenuItemImage* MakeBackButton();
	
	LightManager* m_lightManager;

	int m_maxStageNum;
	int m_stageToPlay;
};