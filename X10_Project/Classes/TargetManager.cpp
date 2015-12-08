#include "stdafx.h"
#include "TargetManager.h"

//Targets
#include "Enemy.h"
#include "Mirror.h"
#include "Mirror_y.h"
#include "Cloud.h"
#include "Bubble.h"
#include "Star.h"
#include "SeeBird.h"
//Stage Information
#include "StageInformation.h"
#include <unordered_map>
#include <functional>

void TargetManager::InitTargets(StageInformation* si)
{
	ResetTargets();

	m_defaultTargetNumber = si->GetTargetCount();
	m_targets.reserve(m_defaultTargetNumber);

	//������ Ŭ������ �´� �Լ������͸� Target* ��ȯ ���·� unordered_map�� ����
	typedef TargetInfo::TargetType TargetType;
	typedef unordered_map<TargetType,std::function<Target*()>>  TargetInfoMap;
	TargetInfoMap targetTypeInfo;
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::ENEMY, Enemy::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::MIRROR, Mirror::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::MIRROR_Y, Mirror_y::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::CLOUD, Cloud::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::BUBBLE, Bubble::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::STAR, Star::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::SEEBIRD, SeeBird::create));

	while (si->HasNextTarget())
	{
		//Ÿ�� Ÿ���� �ҷ��ͼ�
		TargetType type = si->GetTargetType();
		auto createFunction = targetTypeInfo.at(type);	
		//�ű⿡ �´� ���丮 �Լ� ȣ��
		Target* target = createFunction();

		//��ġ, ���� ���� ����
		target->setPosition(si->GetTargetPosition());
		target->setRotation(si->GetTargetRotation());
		target->SetSprScaleRatio(si->GetTargetScale());
		target->SetSprScale(); //sprScaleRatio ���� ���� �������� ������

		//����Ʈ�� ����.
		m_targets.pushBack(target);
	}
}

void TargetManager::ResetTargets()
{
	for (Target* target : m_targets)
	{
		delete target;
	}
	m_targets.clear();
}

void TargetManager::EraseDeadTargets()
{
	Target* target = nullptr;
	for (int i = 0; i < m_targets.size(); i++)
	{
		target = m_targets.at(i);
		if (target->ToBeErased())
		{
			target->removeAllChildrenWithCleanup(true);
			target->removeFromParentAndCleanup(true);
			m_targets.erase(m_targets.begin() + i);
		}
	}
}

bool TargetManager::HasEnemy()
{
	Target* target;
	for (int i = 0; i < m_targets.size(); i++)
	{
		target = m_targets.at(i);
		if (target->IsEnemy())
		{
			return true;
		}
	}
	return false;
}

