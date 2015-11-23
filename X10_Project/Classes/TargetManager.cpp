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
#include <hash_map>
#include <functional>
using namespace stdext;

void TargetManager::InitTargets(StageInformation* si)
{
	ResetTargets();

	m_defaultTargetNumber = si->GetTargetCount();
	m_targets.reserve(m_defaultTargetNumber);

	//각각의 클래스에 맞는 함수포인터 를 void*형태로 hash_map에 저장
	typedef hash_map<string,std::function<Target*()>>  TargetInfoMap;
	TargetInfoMap targetTypeInfo;
	targetTypeInfo.insert(TargetInfoMap::value_type("Enemy", Enemy::create));
	targetTypeInfo.insert(TargetInfoMap::value_type("Mirror", Mirror::create));
	targetTypeInfo.insert(TargetInfoMap::value_type("Mirror_y", Mirror_y::create));
	targetTypeInfo.insert(TargetInfoMap::value_type("Cloud", Cloud::create));
	targetTypeInfo.insert(TargetInfoMap::value_type("Bubble", Bubble::create));
	targetTypeInfo.insert(TargetInfoMap::value_type("Star", Star::create));
	targetTypeInfo.insert(TargetInfoMap::value_type("SeeBird", SeeBird::create));

	while (si->HasNextTarget())
	{
		//타겟 이름을 불러와서
		string type = si->GetTargetType();
		auto createFunction = targetTypeInfo.at(type);	
		//거기에 맞는 팩토리 함수 호출
		Target* target = createFunction();

		//위치, 각도 정보 삽입
		target->setPosition(si->GetTargetPosition());
		target->setRotation(si->GetTargetRotation());
		target->SetSprScaleRatio(si->GetTargetScale());
		target->SetSprScale(); //sprScaleRatio 값에 따라서 스케일이 정해짐

		//리스트에 넣음.
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

void TargetManager::EraseTarget(Target* target)
{
	m_targets.eraseObject(target);
}
