#include "stdafx.h"
#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}

/*


기타 코멘트는 ///# 검색 ㄱㄱ

///# 부분 수정한 뒤에는 코멘트 지우삼..


*/