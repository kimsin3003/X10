#pragma once

class Sling : public Node
{
public: //constant
	const float WIDTH = 20;
	const float HEIGHT = 50;
	const float YPOS = 50;

public:
	static Sling* GetInstance();
	static bool isExist;

	/*동작 변화를 위해 호출하는 함수들*/
	void Reset(); // --> 매스테이지마다 리셋. 매개변수는 미정.
	//sling manager가 있다면 가져가야 할 함수들
	void NewBulletLoad();
	void PullStart(Event* e);
	void Pull(Event* e);
	void Shot(Event* e);
	
	bool IsShoted(); // --> 쐈는지 체크
	Vec2 GetDirection();
	float GetSpeed();
	
private: //function to get singleton instance
	CREATE_FUNC(Sling);
	virtual bool init();
	static Sling* instance;

private: //member function
	enum Status { empty, loaded, pulling, shoted } status;
	void ChangeToLoaded(); //empty -> load
	void ChangeToPulling(); //loaded -> pulling
	void ChangeToShooted(); //pullig -> shooted
	void ChangeToEmpty(); //shooted -> empty

	Point GetStartLocation();

private: //member variable
	Vec2 shootAngle;
	float shootPower;
};