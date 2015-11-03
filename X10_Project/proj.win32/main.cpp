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

- 전반적으로 코딩 컨벤션을 맞추고
  멤버 변수는 앞에 m을 붙인다던지,, { } 위치를 맞춘다든지, 한줄 코드 앞뒤로 줄내림을 하고 {} 할것인지, 대소문자를 어떤식으로 쓸 것인지 등등

- 멤버 변수는 후에 어떤 함수에서 초기화하더라도, 생성시에는 반드시 디폴트 값을 가질 수 있도록 초기화 하는 습관을 만들 것.

- 개경프에서는 최대한 auto를 쓰지 말아 볼 것. 타입 추론에 대한 개념이 확실히 잡힌 후에 auto를 쓰는게 좋다. 

- private / public에 어떤 멤버 함수와 변수를 놓을지 고민 잘 해보고 배치할 것. 귀찮다고 걍 다 public에 놓으면 나중에 기술부채(technical debt)로 돌아온다

- 이제부터는 따로 분리해서 하지말고 하나의 게임 내에서 역할 분담을 해서 진행할 수 있도록.
   Test 부분에 대해서는 아직 코드리뷰를 할 단계가 아니라서 패스..


- 나머지는 "///#" 검색  ㄱㄱ
*/