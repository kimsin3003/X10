#include "stdafx.h"
#include "StageInformation.h"

StageInformation::StageInformation(int stage)
{
	Size winSize = Director::getInstance()->getWinSize();

	if (stage == 0)
	{
		m_currentTargetIndex =0;
		m_currentBulletIndex =0;
		
		TargetInfo info;
		
		info = TargetInfo("Enemy", Point(200, 400), 0, 0.03f);
		m_targetInfoList.push_back(info);

		info = TargetInfo("Cloud", Point(200, 200), 0, 4.0f);
		m_targetInfoList.push_back(info); 
		
		info = TargetInfo("Mirror", Point(30, 200), 0, 3.0f);
		m_targetInfoList.push_back(info);	

		info = TargetInfo("Bubble", Point(200, 300), 0, 2.5f);
		m_targetInfoList.push_back(info);

		info = TargetInfo("Star", Point(100, 250), 0, 0.5f);
		m_targetInfoList.push_back(info);

		//SeeBirds for tests
		Point seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo("SeeBird", seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

		seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo("SeeBird", seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

		seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo("SeeBird", seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

		seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo("SeeBird", seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

		//CrossBullet 3개 Bullet 2개
		string bulletType = "CrossBullet";
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);

		bulletType = "Bullet";
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
	}

	if (stage > 0)
	{
		/*파일에서 정보를 불러서 stage 정보로 채울 부분*/
	}
}

StageInformation::~StageInformation()
{

}

int StageInformation::GetTargetCount()
{// 총 타겟수를 반환
	return m_targetInfoList.size();
}

int StageInformation::GetBulletCount()
{//총 불렛 수를 반환
	return m_bulletInfoList.size();
}

bool StageInformation::HasNextTarget()
{//다음 타겠이 있는지 검사
	if (m_currentTargetIndex < GetTargetCount())
	{
		m_currentTarget = m_targetInfoList.at(m_currentTargetIndex);
		m_currentTargetIndex++;
		return true;
	}
	else 
	{
		return false;
	}
}

string StageInformation::GetTargetType()
{//타겟 타입을 받아옴.
	return m_currentTarget.typeName;
}

Point StageInformation::GetTargetPosition()
{
	return m_currentTarget.position;
}

float StageInformation::GetTargetRotation()
{
	return m_currentTarget.rotation;
}

float StageInformation::GetTargetScale()
{
	return m_currentTarget.scale;
}

bool StageInformation::HasNextBullet() //더 넘길 불렛이 있는지 검사
{
	if (m_currentBulletIndex < GetBulletCount())
	{
		m_currentBullet = m_bulletInfoList.at(m_currentBulletIndex);
		m_currentBulletIndex++;
		return true;
	}
	else
	{
		return false;
	}
}

string StageInformation::GetCurrentBulletInfo() //지금 불렛의 타입을 반환
{
	return m_currentBullet;
}