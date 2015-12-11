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
	enum CONSTANT
	{
		STAR_WIDTH = 15,
		STAR_HEIGHT = 15
	};

	void SetupButtons();
	void SetupCollection();
	void ChangeToMainScene(Ref* pSender);
	Sprite* LoadBackground();
	Sprite* LoadCharacter();
	
	void SetupButtons();
	MenuItemImage* MakeBackButton();
	MenuItemImage* MakeStageButton(int stage, Point pos);
	void ChangeToMainScene(Ref* pSender);
	
	void SetupCollection();

	CollectionManager* m_collectionManager;
	StageButtonPosInformation* m_stageButtonPosInfo;

	Sprite* m_character;

	int m_stageToPlay;
	int m_maxStageNum;
};