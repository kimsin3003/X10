#pragma once

class StageScene : public Layer
{
public:
	enum CONSTANT
	{
		STAR_WIDTH = 20,
		STAR_HEIGHT = 20
	};

	StageScene();
	~StageScene();

	static Scene* CreateScene();
	CREATE_FUNC(StageScene);
	virtual bool init();

	static void GotoStage(Ref* pSender,int stageNum);
	void MenuButtonCallback(Ref* pSender);

private:
	void ChangeToMainScene(Ref* pSender);
	Layer* LoadBackground();
	MenuItemImage* MakeBackButton();
	MenuItemImage* MakeStageButton(int stage, float xPos, float yPos);
};

