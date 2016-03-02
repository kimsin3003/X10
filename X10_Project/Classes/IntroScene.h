#ifndef INTROSCENE_H 
#define INTROSCENE_H

class IntroScene : public LayerColor
{
public:
    static Scene* createScene();
    bool init();
	CREATE_FUNC(IntroScene);

	void PlayAd();

private:
	void WriteText(string text, Point position);
	void _FadeOut();

	void RemoveAllChildren();
	void _FadeIn();
};

#endif