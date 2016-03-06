#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

class TutorialScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(TutorialScene);
	bool init();
	static bool cameFromStageScene;

private:
	void PlaySoundEffect(const char* fileName);
	void PlayExplosion(const Vec2& pos);
	void ChangeToProperScene();
};

#endif