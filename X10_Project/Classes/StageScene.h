#pragma once

class StageScene : public Layer
{
public:
	enum CONSTANT
	{
		STAR_WIDTH = 20,
		STAR_HEIGHT = 20
	};
	const char* BGIMG_FILE = "res/starry_night.jpg"; ///# 이런거 나중에 전부 기술부채가 된다. 한군데 빼서 모아놓도록

	StageScene();
	
	///# 소멸자 구현이 없으면 쓰지 말 것. 특히 아래 소멸자의 경우에는 virtual임에도 그걸 표기하지 않으면서 선언을 해 놓으면 정말 헷갈린다.
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

