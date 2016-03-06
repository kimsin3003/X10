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
	void ChangeToGameScene(Ref* pSender);
private:
	int m_stageNum;
};

#endif