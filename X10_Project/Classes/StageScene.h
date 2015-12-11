#pragma once

class CollectionManager;

class StageScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(StageScene);
	virtual bool init();
	static void GotoStage(Ref* pSender,int stageNum);
	void MenuButtonCallback(Ref* pSender);

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
	MenuItemImage* MakeBackButton();
	MenuItemImage* MakeStageButton(int stage, float xPos, float yPos);
	CollectionManager* collectionManager;
	int m_maxStage;
};