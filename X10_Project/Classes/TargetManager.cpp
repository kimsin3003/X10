#include "stdafx.h"
#include "TargetManager.h"
#include "StageInformation.h"

#include "Mirror.h"
#include "Cloud.h"
#include "Bubble.h"
#include "Enemy.h"
#include "Bubble.h"

#include <hash_map>
using namespace stdext;

TargetManager::TargetManager()
{
	currentTargetIdx = -1;
	defaultTargetNumber = -1;
}

TargetManager::~TargetManager()
{
	targets.clear();
}

void TargetManager::InitTargets(StageInformation* si)
{

	defaultTargetNumber = si->GetTargetCount();
	targets.reserve(defaultTargetNumber);

	//각각의 클래스에 맞는 함수포인터 를 void*형태로 hash_map에 저장
	hash_map<string, void*> targetTypeInfo; //string에 타입 이름.
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Enemy", Enemy::create));
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Mirror", Mirror::create));
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Cloud", Cloud::create));
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Bubble", Bubble::create));

	while (si->HasNextTarget())
	{
		//타겟 이름을 불러와서
		string type = si->GetTargetType();
		void* createFunction = targetTypeInfo.at(type);	
		//거기에 맞는 팩토리 함수 호출
		Target* (*create)() = static_cast<Target* (*)()>(createFunction);
		Target* target = (*create)();

		//위치, 각도 정보 삽입
		target->setPosition(si->GetTargetPosition());
		target->setRotation(si->GetTargetRotation());
		target->SetSprScaleRatio(si->GetTargetScale());
		target->SetSprScale();

		//리스트에 넣음.
		targets.pushBack(target);
	}

	currentTargetIdx = 0;// target 인덱스 세팅. 근데 이거 어디다씀?
}

void TargetManager::EraseTarget(Target* target)
{
	targets.eraseObject(target);
}
