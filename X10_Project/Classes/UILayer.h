#pragma once

class UILayer : public Layer
{
public:
	
	enum CONSTANT{
		PAUSE_BUTTON_WIDTH = 40,
		PAUSE_BUTTON_HEIGHT = 40
	};

	CREATE_FUNC(UILayer);
	static UILayer* createUILayer();
	virtual bool init();

	void menuButtonCallback(Ref* pSender);
private:
	void ChangeToMainScene(Ref* pSender);
};