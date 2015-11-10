#include "stdafx.h"
#include "TargetManager.h"

TargetManager::TargetManager() {
	targets.reserve(5); ///# 이유는? 만일, 예측 가능한 크기 또는 고정크리라면 그냥 std::array를 쓸 것
}
TargetManager::~TargetManager() {}

TargetManager* TargetManager::instance = nullptr;

TargetManager* TargetManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TargetManager();
	}
	return instance;
}