#include "stdafx.h"
#include "MainScene.h"


Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	//Paul's test Page
	auto labelMC = MenuItemFont::create("Paul's Test page", CC_CALLBACK_1(MainScene::ChangeSceneToMC, this));

	// position the label on the center of the screen
	labelMC->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - labelMC->getContentSize().height ));

	auto textHeight = labelMC->getContentSize().height;
	// add the label as a child to this layer
	this->addChild(labelMC, 1);


	auto labelTW = MenuItemFont::create("Kimsin's Test page", CC_CALLBACK_1(MainScene::ChangeSceneToTW, this));

	// position the label on the center of the screen
	labelTW->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - textHeight * 3));

	// add the label as a child to this layer
	this->addChild(labelTW, 1);

	auto labelJW = MenuItemFont::create("FeaterHub's Test page", CC_CALLBACK_1(MainScene::ChangeSceneToJW, this));

	// position the label on the center of the screen
	labelJW->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - textHeight * 5));

	// add the label as a child to this layer
	this->addChild(labelJW, 1);



    //// add "MainScene" splash screen"
    //auto sprite = Sprite::create("MainScene.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}

void MainScene::ChangeSceneToMC(Ref* pSender)
{
	return;
}

void MainScene::ChangeSceneToTW(Ref* pSender)
{
	return;
}

void MainScene::ChangeSceneToJW(Ref* pSender)
{
	return;
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
