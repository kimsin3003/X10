#ifndef INTROSCENE_H
#define INTROSCENE_H

class IntroScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(IntroScene);
	bool init();

private:
	void PlaySoundEffect(const char* fileName);
	void PlayExplosion(const Vec2& pos);
	void ChangeToStageScene();
};

#endif