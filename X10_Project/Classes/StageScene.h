#pragma once

class StageScene : public Layer
{
public:
	enum CONSTANT
	{
		STAR_WIDTH = 20,
		STAR_HEIGHT = 20
	};
	const char* BGIMG_FILE = "res/starry_night.jpg";

	StageScene();
	~StageScene();

	static Scene* CreateScene();
	CREATE_FUNC(StageScene);
	virtual bool init();

	/*스테이지 넘버를 이용해서 넘어가는 함수. 스테이지 버튼에 이 함수와 함수 번호를 넘겨주면 됩니당*/
	static void GotoStage(Ref* pSender,int stageNum);
	
	void MenuButtonCallback(Ref* pSender);

private:
	void ChangeToMainScene(Ref* pSender);
	Sprite* LoadBackground(); //아직 배경 안만듬...
	MenuItemImage* MakeBackButton();
	MenuItemImage* MakeStageButton(int stage, float xPos, float yPos);
};

