#ifndef CREDITSCENE_H
#define CREDITSCENE_H

class CreditScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(CreditScene);
	bool init();

	static float ypos;

private:
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void EndScene();
	Node* createSentence(string str, float fontSize);
	void RemoveAllChildren();
};

#endif