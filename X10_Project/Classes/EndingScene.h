#ifndef ENDING_H
#define ENDING_H

class EndingScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(EndingScene);
	bool init();

private:
	void ShowDeadbody();
	void ShowBlinkingLight();
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
	void SetStreetLight(int isOn);

	Sprite* m_background;
};

#endif