#ifndef STAGESCENE_H
#define STAGESCENE_H

class LightManager;

class StageScene : public LayerColor
{
public:
	static Scene* createScene();
	CREATE_FUNC(StageScene);
	virtual bool init();

private:
	void SetCharacter();
	void SetWaitSign();
	void ChangeToMainScene(Ref* pSender);

	void IntroEvent(float dt);
	
	void ChangeToEndingScene(float dt);

	Sprite* LoadBackground();
	void SetBGM();
	Point GetCharacterPosition(int stage);
	void SetLight();
	MenuItemImage* MakeBackButton();

	void ChangeCharacterToButton(Sprite* characterSprite, Point finalPos, float scale);
	void PlaySound(const char* file);
	static void GotoStage(Ref* pSender, int stageNum);
	void MoveCharacter(Sprite* character, int stageNum);
	static bool m_justCleared;

	LightManager* m_lightManager;
	Sprite* m_background;
	int m_maxStageNum;
	int m_stageToPlay;
};

#endif