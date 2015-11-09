# X10
week3 release 브랜치 :
release_version 에 압축파일이 있습니다. 
실행하시면 나오는 메뉴에서 Kimsin's 에 세가지를 합쳐놓았습니다 .
		Enemy, Explosion 구현 및 Bullet 폭발 조건 설정 - @Paul-Kim
		Bullet , Mirror 제작 및 두 물체 충돌 구현 - @kimsin3003
		발사대 (sling) 제작 - @FeatherHub
		위 세가지 합쳐서 만듬. 


week4 release 브랜치 :
게임 설계 리팩토링  
오브젝트 데이터 관리와 그래픽 레이어 분리.  
그래픽 - GameScene에 GameLayer 와 UILayer로 구성됨.  '

오브젝트 데이터관리. (Manager들은 Singleton) 
GameManager 	- 충돌 관리,  
ColiderManager	- 폭죽 생성, 소멸  
TargetManger	- 타겟리스트 관리.(아직 별 기능이 없네요...)
각각에게 역할 분담.  

Sling 리팩토링  
Explosion 파티클 효과 .   
Bullet redesign  


2015 NEXT 개경프 - 김태우, 김명찬, 최진욱
