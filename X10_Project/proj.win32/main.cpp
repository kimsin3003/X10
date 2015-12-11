#include "stdafx.h"
#include <crtdbg.h>
#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{

	// create the application instance
	AppDelegate app;
	return	Application::getInstance()->run();
}

