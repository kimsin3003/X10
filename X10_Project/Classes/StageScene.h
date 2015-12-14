#pragma once

class CollectionManager;
class StageButtonPosInformation;

class StageScene : public LayerColor
{
public:
	static Scene* createScene();
	CREATE_FUNC(StageScene);
	virtual bool init();
	static void GotoStage(Ref* pSender,int stageNum);

private:
	void SetupButtons();
	void SetupCollection();
	void ChangeToMainScene(Ref* pSender);
	
	void IntroEvent(float dt);
	void PrintIntroPage(const string fileDir, float startTime, float keepTime);
	void PrintIntroText(const string message, const Vec2 pos, float startTime, float keepTime);
	
	void EndingEvent(float dt);
	void Take01(float startTime);
	void Take02(float startTime);
	void Take03(float startTime);
	void Take04(float startTime);
	void Take05(float startTime);
	void Take06(float startTime);
	void Take07(float startTime);
	void Take08(float startTime);
	void Take09(float startTime);
	void Take10(float startTime);

	Repeat* CreateSpark(float blackTime, float whiteTime, int repeatTime);

	Sprite* LoadBackground();
	Sprite* LoadCharacter();
	MenuItemImage* MakeBackButton();
	MenuItemImage* MakeStageButton(int stage, Point pos);
	
	CollectionManager* m_collectionManager;
	StageButtonPosInformation* m_stageButtonPosInfo;

	Sprite* m_character;

	int m_maxStageNum;
	int m_stageToPlay;
};