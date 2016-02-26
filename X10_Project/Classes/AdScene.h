#ifndef ADSCENE
#define ADSCENE
#include "stdafx.h"
#include "ConstVars.h"
#include "FileStuff.h"


class AdScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(AdScene);
	bool init();
	void PlayAd();
	void ExitScene();
	void update(float dt);

private:
	float lifeTime;

};

#endif