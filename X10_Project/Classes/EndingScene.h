#pragma once
class EndingScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(EndingScene);
	bool init();

private:

	void ShowCrashingScene();
	void ChangeSoundEffect(const char* sound);
	void ChangeBackgroundImg(string bgImg);
	void ChangeToCreditScene();
	void AddMonitor();
	void FadeOut();
	void ShowAfterCrash();
	void ShowHospital();
	void ShowWhiteScene();
	void RemoveAllChildren();

	Sprite* m_background;
};

