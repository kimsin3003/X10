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

	Sprite* testSpr = Sprite::create(FileStuff::LIGHT_BEAM);
	addChild(testSpr);

	testSpr->runAction(MoveBy::create(3.0f, Vec2(150, 150)));

	Sequence* seq = Sequence::create(
		DelayTime::create(3.0f),
		CallFuncN::create(CC_CALLBACK_1(AdScene::ChangeToGameScene, this)),
		nullptr);

	runAction(seq);
}

void AdScene::ChangeToGameScene(Ref* pSender)
{
	int stageNum = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTWALKSTAGE);

	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));

	GameManager* gameManager = GameManager::GetInstance();
	gameManager->SetUILayer(gameScene->GetUILayer());
	gameManager->SetGameLayer(gameScene->GetGameLayer());
	gameManager->SetStage(stageNum);

	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);
	Director::getInstance()->replaceScene(sceneWithEffect);
}
