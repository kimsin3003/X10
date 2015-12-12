#pragma once

class MapEditer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void SetCallBackFuncs();
	CREATE_FUNC(MapEditer);

private:
	Layer* m_layer;
	void Save();
	void OnMouseMove(Event* event);
	void OnMouseUp(Event* event);
	void onMouseDown(EventMouse* event);
	void OnMouseScroll(Event* event);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode);
	EventKeyboard::KeyCode m_pressedKey;
};
