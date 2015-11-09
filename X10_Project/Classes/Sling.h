#pragma once

class Sling : public Node
{
public: //constant
	const float WIDTH	= 20;
	const float HEIGHT	= 50;
	const float YPOS	= 50;
	const float MAX_POWER	= 50;
	const float FONT_SIZE	= 24;
	const float PREDICT_LINE_TIME = 0.5;

public:
	static Sling* GetInstance();
	static bool isExist;

	/*동작 변화를 위해 호출하는 함수들*/
	void Reset(); // --> 매스테이지마다 리셋. 매개변수는 미정.
	void NewColliderLoad();
	void PullStart(Event* e);
	void Pull(Event* e);
	void Shot(Event* e);
	
	bool IsShotted(); // --> 쐈는지 체크
	Vec2 GetDirection();
	float GetAngleInRadian();
	float GetSpeed();
	
	
private: //function to get singleton instance
	CREATE_FUNC(Sling);
	virtual bool init();
	static Sling* instance;

	//member function
	enum Status { empty, loaded, pulling, shotted } status;
	void ChangeToLoaded();	//empty -> load
	void ChangeToPulling(); //loaded -> pulling
	void ChangeToShotted(); //pullig -> shotted
	void ChangeToEmpty();	//shotted -> empty

	Point GetStartLocation();

private: //member variable
	Vec2 shotAngle;
	float shotPower;
};