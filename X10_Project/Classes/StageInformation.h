#pragma once

class StageInformation
{
public:

	StageInformation(int stage);
	~StageInformation();
	int GetTargetCount();//총 타겟 수를 반환
	int GetBulletCount();//총 불렛 수를 반환
	
	bool HasNextTarget(); // 더 넘길 타겟이 있는지 검사
	string GetTargetType(); //타겟의 타입을 반환
	Point GetTargetPosition(); //타겟 위치 반환
	float GetTargetRotation(); //타겟 돌아간 정도 반환
	float GetTargetScale(); //타겟 스케일 반환
	
	bool HasNextBullet(); //더 넘길 불렛이 있는지 검사
	string GetCurrentBulletInfo(); //지금 불렛의 타입을 반환

private:

	struct TargetInfo //정보 묶음용 이너 클래스...struct로 할껄.
	{
	public:
		string typeName;
		Point position;
		float rotation;
		float scale;

		TargetInfo() : TargetInfo("", Point::ZERO, 0, 0)
		{};
		TargetInfo(string str, Point p, float r, float s) : typeName(str), position(p), rotation(r), scale(s)
		{};
		~TargetInfo(){}
	};


	const char* FILENAME = "temp.txt";
	int m_currentTargetIndex;
	int m_currentBulletIndex;
	TargetInfo m_currentTarget;
	string m_currentBullet;
	vector<TargetInfo> m_targetInfoList;
	vector<string> m_bulletInfoList;
};

