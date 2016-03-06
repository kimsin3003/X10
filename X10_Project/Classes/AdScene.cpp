#include "stdafx.h"
#include "AdScene.h"
#include "AdmobHelper.h"
#include "GameScene.h"
#include "GameManager.h"

Scene* AdScene::createScene()
{
	Scene* scene = Scene::create();

	Layer* layer = AdScene::create();
	scene->addChild(layer);

	return scene;
}

bool AdScene::init(){

	if (!Layer::init())
	{
		return false;
	}

	Size screenSize = Director::getInstance()->getVisibleSize();
	float width = screenSize.width;
	float height = screenSize.height;

	Label* adLabel = Label::create("Ad time. We're hungry", FileStuff::FONT_ARIAL, 24.0f);
	adLabel->setPosition(width / 2.0f, height / 2.0f);
	addChild(adLabel);

	AdmobHelper::showAd();

	Sequence* seq = Sequence::create(
		DelayTime::create(1.0f),
		CallFuncN::create(CC_CALLBACK_1(AdScene::ChangeToGameScene, this)),
		nullptr);

	runAction(seq);

	return true;
}

void AdScene::ChangeToGameScene(Ref* pSender)
{
	int stageNum = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));

	GameManager* gameManager = GameManager::GetInstance();
	gameManager->SetUILayer(gameScene->GetUILayer());
	gameManager->SetGameLayer(gameScene->GetGameLayer());
	gameManager->SetStage(stageNum);

	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);
	Director::getInstance()->replaceScene(sceneWithEffect);

	return;
}
