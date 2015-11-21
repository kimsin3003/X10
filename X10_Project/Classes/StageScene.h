#pragma once

class StageScene : public Layer
{
public:
	
	StageScene();
	~StageScene();

	static Scene* CreateScene();
	CREATE_FUNC(StageScene);
	virtual bool init();

	void MenuButtonCallback(Ref* pSender);
private:
	void ChangeToMainScene(Ref* pSender);
	Layer* LoadBackground();
	MenuItemImage* MakeBackButton();
};

