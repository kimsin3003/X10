#ifndef STAGEINFO_H 
#define STAGEINFO_H

#include "FileStuff.h"

struct TargetPoint
{
	float x;
	float y;
	TargetPoint() :x(0), y(0)
	{};
	TargetPoint(float x, float y) : x(x), y(y)
	{};

	Point get()
	{ 
		return Point(x, y); 
	}

	void set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct TargetInfo //���� ������ inner struct
{
public:
	enum TargetType
	{
		ENEMY,
		MIRROR,
		VIRTICAL_MIRROR,
		CLOUD,
		BUBBLE,
		STAR,
		GULL
	};

	TargetType m_name;
	TargetPoint m_position;
	TargetPoint m_scale;
	float m_rotation;

	TargetInfo() : TargetInfo(TargetType::ENEMY, TargetPoint()) {}
	TargetInfo(TargetType name, TargetPoint p, float r = 0.0f, float scalex = 1.0f, float scaley = 1.0f)
		: m_name(name), m_position(p), m_rotation(r), m_scale(TargetPoint(scalex, scaley))
	{}
	~TargetInfo(){}

};

class StageInformation
{
public:
	explicit StageInformation(int stage);
	~StageInformation();
	int GetTargetCount();//�� Ÿ�� ���� ��ȯ
	int GetBulletCount();//�� �ҷ� ���� ��ȯ
	
	bool HasNextTarget(); // �� �ѱ� Ÿ���� �ִ��� �˻�
	TargetInfo::TargetType GetTargetType(); //Ÿ���� Ÿ���� ��ȯ
	Point GetTargetPosition(); //Ÿ�� ��ġ ��ȯ
	float GetTargetRotation(); //Ÿ�� ���ư� ���� ��ȯ
	float GetTargetScale(); //Ÿ�� ������ ��ȯ
	
	bool HasNextBullet(); //�� �ѱ� �ҷ��� �ִ��� �˻�
	string GetCurrentBulletInfo(); //���� �ҷ��� Ÿ���� ��ȯ
	static int GetMaxStageNum(){ return m_maxStageNum; }

	bool MakeJsonFileFromLayer(Layer* layer, const string& fileName = FileStuff::EDITING_FILENAME);

private:
	static const int m_maxStageNum = 13;
	int m_currentTargetIndex;
	int m_currentBulletIndex;

	static const int BUFFERSIZE = 65536;
	TargetInfo m_currentTarget;
	string m_currentBullet;
	vector<TargetInfo> m_targetInfoList;
	vector<string> m_bulletInfoList;
};

struct cppson
{
	static bool loadFile(vector<TargetInfo> infoList, string fileName);
	static bool loadFile(vector<string> bulletList, string fileName);
	static bool toJson(vector<TargetInfo> infoList, string fileName);
};

typedef TargetInfo::TargetType TargetType;

//
//JSON_CLASS(TargetPoint)
//{
//public:
//	FIELD(float, x);
//	FIELD(float, y);
//
//	operator Point() const
//	{
//		return Point(x, y);
//	}
//
//};
//
//JSON_CLASS(TargetInfo) //���� ������ inner struct
//{
//public:
//	enum TargetType
//	{
//		ENEMY,
//		MIRROR,
//		VIRTICAL_MIRROR,
//		CLOUD,
//		BUBBLE,
//		STAR,
//		GULL
//	};
//
//	FIELD_WITH_KEY(TargetType, type, m_name);
//	FIELD_WITH_KEY(TargetPoint, position, m_position);
//	FIELD_WITH_KEY(TargetPoint, scale, m_scale);
//	FIELD_WITH_KEY(float, rotation, m_rotation);
//
//	~TargetInfo() {}
//};
//	

#endif