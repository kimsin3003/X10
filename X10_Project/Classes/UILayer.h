#pragma once

class UILayer : public Layer
{

public:
	CREATE_FUNC(UILayer);
	static UILayer* createUILayer();
	virtual bool init();
};