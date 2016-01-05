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
	void AddMonitor();
	void FadeOut();
	void ShowAfterCrash();
	void ShowHospital();
	void ShowWhiteScene();
	void RemoveAllChildren(Ref* pSender);
	void PrintIntroText(const string& message, const Vec2& pos, float startTime, float textScale);
	Sprite* m_background;
};

