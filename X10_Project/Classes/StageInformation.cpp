#include "stdafx.h"
#include "StageInformation.h"
#include <fstream>
#include <iostream>
#include <string>
#include <json/json.h>

bool cppson::loadFile(vector<TargetInfo> infoList, string fileName)
{
	return true;
}

bool cppson::loadFile(vector<string> bulletList, string fileName)
{
	return true;
}

bool cppson::toJson(vector<TargetInfo> infoList, string fileName)
{
	return true;
}


StageInformation::StageInformation(int stage) : 
m_currentTargetIndex(0), m_currentBulletIndex(0),
m_currentTarget(), m_currentBullet()
{
	TargetInfo info;

	if (stage >= 0)
	{
		/*load targets*/
		char fileName[100];
		sprintf(fileName, "files/target%d.json", stage);

		//load from file
		if (!cppson::loadFile(m_targetInfoList, fileName))
		{
			CCLOG("Target Load Fail.");
			return;
		}

		/*load bullets*/
		sprintf(fileName, "files/bullet%d.json", stage);

		//load from file
		if (!cppson::loadFile(m_bulletInfoList, fileName))
		{
			CCLOG("Target Load Fail.");
			return;
		}
	}
}

StageInformation::~StageInformation()
{
	m_targetInfoList.clear();
	m_bulletInfoList.clear();
}

int StageInformation::GetTargetCount()
{// �� Ÿ�ټ��� ��ȯ
	return m_targetInfoList.size();
}

int StageInformation::GetBulletCount()
{//�� �ҷ� ���� ��ȯ
	return m_bulletInfoList.size();
}

bool StageInformation::HasNextTarget()
{//���� Ÿ���� �ִ��� �˻�
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
{//Ÿ�� Ÿ���� �޾ƿ�.
	return m_currentTarget.m_name;
}

Point StageInformation::GetTargetPosition()
{
	return m_currentTarget.m_position.get();
}

float StageInformation::GetTargetRotation()
{
	return m_currentTarget.m_rotation;
}

float StageInformation::GetTargetScale()
{
	return (m_currentTarget.m_scale.x +m_currentTarget.m_scale.y)/2;
}

bool StageInformation::HasNextBullet() //�� �ѱ� �ҷ��� �ִ��� �˻�
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

string StageInformation::GetCurrentBulletInfo() //���� �ҷ��� Ÿ���� ��ȯ
{
	return m_currentBullet;
}

bool StageInformation::MakeJsonFileFromLayer(Layer* layer, const string& fileName)
{
	//stageInformaition ��ü�� �̿��� filename�� Json ���Ϸ� ����.
	m_targetInfoList.clear();

	for (Node* child : layer->getChildren())
	{
		TargetInfo targetInfo;
		
		targetInfo.m_name = static_cast<TargetType>(child->getTag());
		targetInfo.m_rotation = child->getRotation();
		TargetPoint scale;
		scale.x = child->getScaleY();
		scale.y = child->getScaleY();

		targetInfo.m_scale = scale;
		
		TargetPoint position;
		position.x = child->getPositionX();
		position.y = child->getPositionY();
		targetInfo.m_position = position;

		m_targetInfoList.push_back(targetInfo);
	}
	
	//write to file
	if (!cppson::toJson(m_targetInfoList, fileName))
	{
		CCLOG("Target write Fail.");
		return false;
	}
	return true;
}