#pragma once

class CollectionManager;
class StageButtonPosInformation;

class StageScene : public Layer
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