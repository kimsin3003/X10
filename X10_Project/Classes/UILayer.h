#pragma once

class UILayer : public Layer
{
public:
	const float PAUSE_BUTTON_WIDTH = 40;
	const float PAUSE_BUTTON_HEIGHT = 40;

public:
	CREATE_FUNC(UILayer);
	static UILayer* createUILayer();
	virtual bool init();

	void menuButtonCallback(Ref* pSender);
private:
	void ChangeToMainScene(Ref* pSender);
};