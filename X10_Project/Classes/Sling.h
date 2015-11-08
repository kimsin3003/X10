#pragma once

class Sling : public Node
{
public:
	static Sling* GetInstance();
	void Reset(); // --> 매스테이지마다 리셋. 매개변수는 미정.
	bool IsShoted(); // --> 쐈는지 체크
	Vec2 GetDirection();
	float GetSpeed();
private:
	static Sling* instance;
};