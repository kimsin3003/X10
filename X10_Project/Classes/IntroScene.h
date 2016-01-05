#pragma once
class IntroScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(IntroScene);
	bool init();

	void Text1(Ref* pSender);
	void Text2(Ref* pSender);
	void RemoveAllChildren(Ref* pSender);
	void ChangeToStageScene(Ref* pSender);
private:
	void PrintIntroText(const string& message, const Vec2& pos, float startTime, float textScale);
};
