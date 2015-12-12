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
	Sprite* LoadBackground();
	Sprite* LoadCharacter();
	MenuItemImage* MakeBackButton();
	MenuItemImage* MakeStageButton(int stage, Point pos);
	
	CollectionManager* m_collectionManager;
	StageButtonPosInformation* m_stageButtonPosInfo;

	Sprite* m_character;

	int m_stageToPlay;
	int m_maxStageNum;
};