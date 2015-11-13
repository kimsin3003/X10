#include "stdafx.h"
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE__)
#endif
#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// create the application instance
	AppDelegate app;
	return	Application::getInstance()->run();
}
/*


기타 코멘트는 ///# 검색 ㄱㄱ

///# 부분 수정한 뒤에는 코멘트 지우삼..


*/