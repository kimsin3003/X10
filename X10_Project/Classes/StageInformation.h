#pragma once
#include "cppson.h"
#include "FileStuff.h"

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

JSON_CLASS(TargetInfo) //���� ������ inner struct
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

	FIELD_WITH_KEY(TargetType, type, m_name);

	FIELD_WITH_KEY(TargetPoint, position, m_position);
	FIELD_WITH_KEY(float, rotation, m_rotation);
	FIELD_WITH_KEY(TargetPoint, scale, m_scale);

	~TargetInfo() {}
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

	bool MakeJsonFileFromLayer(Layer* layer, string fileName = FileStuff::EDITING_FILENAME);

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

typedef TargetInfo::TargetType TargetType;
