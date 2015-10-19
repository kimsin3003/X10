#include "AppDelegate.h"
#include "MainScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

<<<<<<< HEAD
AppDelegate::AppDelegate() {

=======
/*

	拙失切: 置遭錐
	奄管: Main Scene 聖 鉢檎 段奄拭 稽球獣轍陥.
	Main Scene 聖 適遣馬檎 Game Scene 戚 稽球吉陥.
	戚凶 Main Scene 精 五乞軒拭辞 背薦誼陥.
*/
AppDelegate::AppDelegate() 
{
>>>>>>> 21acecd2a44d0818cb278044ed7e8d3c2066678f
}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
<<<<<<< HEAD
	斗閃隅 斗閃虞焼焼た焼焼焼た焼焼辞っさい原杖;びた耕馬耕紫っ戚たば備たし�で擦奮mず
=======
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
>>>>>>> 21acecd2a44d0818cb278044ed7e8d3c2066678f
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
<<<<<<< HEAD
        glview = GLViewImpl::createWithRect("SceneTest", Rect(0, 0, mediumResolutionSize.width, mediumResolutionSize.height));
#else
        glview = GLViewImpl::create("SceneTest");
=======
        glview = GLViewImpl::createWithRect("cocotest", Rect(0, 0, 480, 320));
#else
        glview = GLViewImpl::create("cocotest");
>>>>>>> 21acecd2a44d0818cb278044ed7e8d3c2066678f
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
<<<<<<< HEAD
    director->setDisplayStats(true);
=======
    director->setDisplayStats(false);
>>>>>>> 21acecd2a44d0818cb278044ed7e8d3c2066678f

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    Size frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
