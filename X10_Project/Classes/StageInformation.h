#pragma once
#include "cppson.h"


JSON_CLASS(TargetPoint)
{
public:
	FIELD(float, x);
	FIELD(float, y);

	operator Point() const
	{
		return Point(x, y);
	}

};

JSON_CLASS(TargetInfo) //정보 묶음용 inner struct
{
public:
	enum TargetType
	{
		ENEMY,
		MIRROR,
		MIRROR_Y,
		CLOUD,
		BUBBLE,
		STAR,
		SEEBIRD
	};

	FIELD_WITH_KEY(TargetType, type, m_name);

	FIELD_WITH_KEY(TargetPoint, position, m_position);
	FIELD_WITH_KEY(float, rotation, m_rotation);
	FIELD_WITH_KEY(TargetPoint, scale, m_scale);

	~TargetInfo() {}
};

class StageInformation
{
public:

	StageInformation(int stage);
	~StageInformation();
	int GetTargetCount();//총 타겟 수를 반환
	int GetBulletCount();//총 불렛 수를 반환
	
	bool HasNextTarget(); // 더 넘길 타겟이 있는지 검사
	TargetInfo::TargetType GetTargetType(); //타겟의 타입을 반환
	Point GetTargetPosition(); //타겟 위치 반환
	float GetTargetRotation(); //타겟 돌아간 정도 반환
	float GetTargetScale(); //타겟 스케일 반환
	
	bool HasNextBullet(); //더 넘길 불렛이 있는지 검사
	string GetCurrentBulletInfo(); //지금 불렛의 타입을 반환
	static int GetMaxStageNum(){ return m_maxStageNum; }

	bool MakeJsonFileFromLayer(Layer* layer, const char* fileName = "temp.json");


private:
	static const int m_maxStageNum = 17;
	const char* FILENAME = "temp.txt";
	int m_currentTargetIndex;
	int m_currentBulletIndex;

	static const int BUFFERSIZE = 65536;
	TargetInfo m_currentTarget;
	string m_currentBullet;
	vector<TargetInfo> m_targetInfoList;
	vector<string> m_bulletInfoList;
};

typedef TargetInfo::TargetType TargetType;
