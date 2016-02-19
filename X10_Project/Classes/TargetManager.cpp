#include "stdafx.h"
#include "StageInformation.h"
#include "TargetManager.h"
//Targets
#include "Enemy.h"
#include "Mirror.h"
#include "Virtical_Mirror.h"
#include "Bubble.h"
#include "Stone.h"
//Stage Information
#include <unordered_map>
#include <functional>

void TargetManager::InitTargets(StageInformation* si)
{
	ResetTargets();

	m_defaultTargetNumber = si->GetTargetCount();
	m_targets.reserve(m_defaultTargetNumber);

	//������ Ŭ������ �´� �Լ������͸� Target* ��ȯ ���·� unordered_map�� ����
	typedef unordered_map<int,std::function<Target*()>>  TargetInfoMap;
	TargetInfoMap targetTypeInfo;
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::ENEMY, Enemy::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::MIRROR, Mirror::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::VIRTICAL_MIRROR, Virtical_Mirror::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::BUBBLE, Bubble::create));
	targetTypeInfo.insert(TargetInfoMap::value_type(TargetInfo::STAR, Stone::create));

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
	for (int i = 0; i < m_targets.size(); i++)
	{
		Target* target = m_targets.at(i);
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
	for (int i = 0; i < m_targets.size(); i++)
	{
		Target* target = m_targets.at(i);
		if (target->IsEnemy() && target->IsApplyable())
		{
			return true;
		}
	}
	return false;
}
