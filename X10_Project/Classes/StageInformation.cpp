#include "stdafx.h"
#include "StageInformation.h"
#include <fstream>

StageInformation::StageInformation(int stage)
{
	Size winSize = Director::getInstance()->getWinSize();
	m_currentTargetIndex = 0;
	m_currentBulletIndex = 0;

	TargetInfo info;

	if (stage <= 1 && stage >=0)
	{
		char fileName[100];
		sprintf(fileName, "../Resources/files/target%d.txt", stage);
		ifstream ifs(fileName);

		while (!ifs.eof())
		{
			int type;
			float posX, posY, rotation, scaleX, scaleY;
			ifs >> type >> posX >> posY >> rotation >> scaleX >> scaleY;
			info = TargetInfo(static_cast<TargetType>(type), Point(posX, posY), rotation, scaleX, scaleY);
			m_targetInfoList.push_back(info);
		}

		sprintf(fileName, "../Resources/files/bullet%d.txt", stage);
		ifs = ifstream(fileName);

		while (!ifs.eof())
		{
			int crossnum, bulletnum;
			ifs >> crossnum >> bulletnum;

			string bulletType = "CrossBullet";
			for (int i = 0; i < crossnum; i++)
			{
				m_bulletInfoList.push_back(bulletType);
			}

			bulletType = "Bullet";
			for (int i = 0; i < bulletnum; i++)
			{
				m_bulletInfoList.push_back(bulletType);
			}

		}

		return;

		//SeeBirds ... 파일에서 어떻게 읽어오지...
		Point seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo(TargetInfo::SEEBIRD, seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

		seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo(TargetInfo::SEEBIRD, seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

		seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo(TargetInfo::SEEBIRD, seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

		seeBirdPos = Point(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
		info = TargetInfo(TargetInfo::SEEBIRD, seeBirdPos, 0, 1.0f);
		m_targetInfoList.push_back(info);

	}
	else if (stage == 2)
	{
		/// 만일 테스트 용이라면 테스트용이라고 꼭 명시를 할 것.
		info = TargetInfo(TargetInfo::ENEMY, Point(160, 280), 0, 1.03f);
		m_targetInfoList.push_back(info);

		for (int j = 0; j <= 17; j++)
		{
			info = TargetInfo(TargetInfo::BUBBLE, Point(160 + j * 10, 100 + j * 15), 0, 2.5f / 2);
			m_targetInfoList.push_back(info);
		}

		for (int j = 0; j <= 17; j++)
		{
			info = TargetInfo(TargetInfo::BUBBLE, Point(160 - j * 10, 100 + j * 15), 0, 2.5f / 2);
			m_targetInfoList.push_back(info);
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j <= i * 2 - 1; j++)
			{
				info = TargetInfo(TargetInfo::STAR, Point(180 + (j * 15) - (i * 20), 175 + (i * 20)), i * 30 + j * 2, 0.5f / 2);
				m_targetInfoList.push_back(info);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j <= i * 2 - 1; j++)
			{
				info = TargetInfo(TargetInfo::STAR, Point(180 + (j * 15) - (i * 20), 385 - (i * 20)), i * 30 + j * 2, 0.5f / 2);
				m_targetInfoList.push_back(info);
			}
		}

		//Bullet 5개`
		string bulletType = "Bullet";
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
	}
	else if (stage == 3)
	{

		Size screen = Director::getInstance()->getVisibleSize();

		info = TargetInfo(TargetInfo::MIRROR, Point(0, 200), 0, 1.5);
		m_targetInfoList.push_back(info);
		info = TargetInfo(TargetInfo::MIRROR, Point(320, 200), 0, 1.5f);
		m_targetInfoList.push_back(info);

		info = TargetInfo(TargetInfo::MIRROR, Point(160, 300), 0, 3.0f / 2);
		m_targetInfoList.push_back(info);

		info = TargetInfo(TargetInfo::MIRROR_Y, Point(160, 100), 0, 2.5f / 2);
		m_targetInfoList.push_back(info);
		info = TargetInfo(TargetInfo::MIRROR_Y, Point(70, 250), 0, 2.5f / 2);
		m_targetInfoList.push_back(info);


		info = TargetInfo(TargetInfo::ENEMY, Point(300, 360), 0, 3.0f);
		m_targetInfoList.push_back(info);
		info = TargetInfo(TargetInfo::MIRROR, Point(0, 360), 0, 1.5);
		m_targetInfoList.push_back(info);
		info = TargetInfo(TargetInfo::MIRROR, Point(320, 360), 0, 1.5f);
		m_targetInfoList.push_back(info);

		for (int xpos = 0; xpos < screen.width + 40; xpos += 34)
		{
			info = TargetInfo(TargetInfo::MIRROR_Y, Point(xpos, 480), 0, 2.5f / 2);
			m_targetInfoList.push_back(info);
		}

		info = TargetInfo(TargetInfo::STAR, Point(100, 250), 0, 0.25f);
		m_targetInfoList.push_back(info);

		info = TargetInfo(TargetInfo::STAR, Point(250, 250), 0, 0.25f);
		m_targetInfoList.push_back(info);
		info = TargetInfo(TargetInfo::STAR, Point(260, 250), 0, 0.25f);
		m_targetInfoList.push_back(info);

		info = TargetInfo(TargetInfo::STAR, Point(230, 210), 0, 0.25f);
		m_targetInfoList.push_back(info);

		info = TargetInfo(TargetInfo::STAR, Point(220, 190), 0, 0.25f);
		m_targetInfoList.push_back(info);
		info = TargetInfo(TargetInfo::STAR, Point(230, 190), 0, 0.25f);
		m_targetInfoList.push_back(info);

		//Bullet 5개
		string bulletType = "Bullet";
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
		m_bulletInfoList.push_back(bulletType);
	}
	else
	{

	}
}

StageInformation::~StageInformation()
{
	m_targetInfoList.clear();
	m_bulletInfoList.clear();
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

TargetType StageInformation::GetTargetType()
{//타겟 타입을 받아옴.
	return m_currentTarget.m_name;
}

Point StageInformation::GetTargetPosition()
{
	return m_currentTarget.m_position;
}

float StageInformation::GetTargetRotation()
{
	return m_currentTarget.m_rotation;
}

float StageInformation::GetTargetScale()
{
	return (m_currentTarget.m_scaleX +m_currentTarget.m_scaleY)/2;
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