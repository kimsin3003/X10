#ifndef CREDITSCENE_H
#define CREDITSCENE_H

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

#endif