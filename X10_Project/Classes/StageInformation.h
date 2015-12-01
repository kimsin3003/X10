#pragma once


class StageInformation
{
public:
	struct TargetInfo //정보 묶음용 inner struct
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
		} m_name;
		
		Point m_position;
		float m_rotation;
		float m_scaleX;
		float m_scaleY;

		TargetInfo() : TargetInfo(TargetType::ENEMY, Point::ZERO) {}
		TargetInfo(TargetType name, Point p, float r = 0.0f, float scalex = 1.0f, float scaley = 1.0f)
			: m_name(name), m_position(p), m_rotation(r), m_scaleX(scalex), m_scaleY(scaley)
		{}
		~TargetInfo(){}
	};

	StageInformation(int stage);
	~StageInformation();
	int GetTargetCount();//총 타겟 수를 반환
	int GetBulletCount();//총 불렛 수를 반환
	
	bool HasNextTarget(); // 더 넘길 타겟이 있는지 검사
	StageInformation::TargetInfo::TargetType GetTargetType(); //타겟의 타입을 반환
	Point GetTargetPosition(); //타겟 위치 반환
	float GetTargetRotation(); //타겟 돌아간 정도 반환
	float GetTargetScale(); //타겟 스케일 반환
	
	bool HasNextBullet(); //더 넘길 불렛이 있는지 검사
	string GetCurrentBulletInfo(); //지금 불렛의 타입을 반환
	static int GetMaxStageNum(){ return m_maxStageNum; }


private:

	const char* FILENAME = "temp.txt";
	int m_currentTargetIndex;
	int m_currentBulletIndex;
	static const int m_maxStageNum = 3;
	TargetInfo m_currentTarget;
	string m_currentBullet;
	vector<TargetInfo> m_targetInfoList;
	vector<string> m_bulletInfoList;
};

typedef StageInformation::TargetInfo::TargetType TargetType;
