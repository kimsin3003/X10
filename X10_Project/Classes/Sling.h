#pragma once

class Sling : public Node
{
public:

	enum SLING_CONFIG
	{
		WIDTH	= 20,
		HEIGHT	= 50,
		YPOS	= 50,
		MAX_POWER = 30,
		CLICK_RANGE = 10,
	};

	const float FONT_SIZE	= 24;
	const float PREDICT_LINE_TIME = 0.5;
	
public:
	CREATE_FUNC(Sling);

	/*동작 변화를 위해 호출하는 함수들*/
	void Reset(); // --> 매스테이지마다 리셋. 매개변수는 미정.
	void LoadBullet();
	void ShotComplete();
	void PullStart(Event* e);
	void Pull(Event* e);
	void Shot(Event* e);
	
	bool IsShotted(); // --> 쐈는지 체크
	Vec2 GetDirection();
	float GetAngleInRadian();
	float GetSpeed();
	float GetRotationAngle();
	
private: 
	//function to get singleton instance
	virtual bool init();
	
	int m_status;
	enum STATUS 
	{ 
		EMPTY, 
		LOADED,
		PULLING,
		SHOTTED 
	};

	void ChangeToLoaded();	//empty -> load
	void ChangeToPulling(); //loaded -> pulling
	void ChangeToShotted(); //pullig -> shotted
	void ChangeToEmpty();	//shotted -> empty

	Point GetStartLocation();

	//member variable to make 'Shot Infomation'
	Vec2 m_shotAngle;
	float m_shotPower;
};