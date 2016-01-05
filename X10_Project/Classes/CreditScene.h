#pragma once
class CreditScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(CreditScene);
	bool init();

	void EndScene();
	static float ypos;

private:
	Node* createSentence(string str, float fontSize);
	void RemoveAllChildren();
};

