#pragma once

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
		STAR_WIDTH = 20,
		STAR_HEIGHT = 20
	};

	void SetupButtons();
	void ChangeToMainScene(Ref* pSender);
	Sprite* LoadBackground();
	MenuItemImage* MakeBackButton();
	MenuItemImage* MakeStageButton(int stage, float xPos, float yPos);
	int m_maxStage;
};