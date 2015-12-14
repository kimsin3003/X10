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
	void LeftMouseDown(EventMouse* event);
	void RightMouseDown(EventMouse* event);
	void WheelDown(EventMouse* event);
	void onMouseDown(EventMouse* event);
	void OnMouseScroll(EventMouse* event);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode);
	EventKeyboard::KeyCode m_pressedKey;
	Node* m_clicked_sprite;
};
