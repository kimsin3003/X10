#include "stdafx.h"
#include "StageInformation.h"

StageInformation::StageInformation(int stage)
{
	//0탄 임시 페이지
	if (stage == 0)
	{
		CurrentTargetIndex =0;
		CurrentBulletIndex =0;
		
		TargetInfo info;
		
		info = TargetInfo("Enemy", Point(200, 400), 0, 0.03f);
		TargetInfoList.push_back(info);

		info = TargetInfo("Mirror", Point(30, 200),0, 3.0f);
		TargetInfoList.push_back(info);

		info = TargetInfo("Cloud", Point(200, 200), 0, 4.0f);
		TargetInfoList.push_back(info);

		info = TargetInfo("Bubble", Point(200, 300), 0, 2.5f);
		TargetInfoList.push_back(info);

		//bullet 다섯개
		string bulletType = "Bullet";
		BulletInfoList.push_back(bulletType);
		BulletInfoList.push_back(bulletType);
		BulletInfoList.push_back(bulletType);
		BulletInfoList.push_back(bulletType);
		BulletInfoList.push_back(bulletType);
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
	return TargetInfoList.size();
}

int StageInformation::GetBulletCount()
{//총 불렛 수를 반환
	return BulletInfoList.size();
}

bool StageInformation::HasNextTarget()
{//다음 타겠이 있는지 검사
	if (CurrentTargetIndex < GetTargetCount())
	{
		currentTarget = TargetInfoList.at(CurrentTargetIndex);
		CurrentTargetIndex++;
		return true;
	}
	else 
	{
		return false;
	}
}

string StageInformation::GetTargetType()
{//타겟 타입을 받아옴.
	return currentTarget.typeName;
}

Point StageInformation::GetTargetPosition()
{
	return currentTarget.position;
}

float StageInformation::GetTargetRotation()
{
	return currentTarget.rotation;
}

float StageInformation::GetTargetScale()
{
	return currentTarget.scale;
}

bool StageInformation::HasNextBullet() //더 넘길 불렛이 있는지 검사
{
	if (CurrentBulletIndex < GetBulletCount())
	{
		currentBullet = BulletInfoList.at(CurrentBulletIndex);
		CurrentBulletIndex++;
		return true;
	}
	else
	{
		return false;
	}
}

string StageInformation::GetCurrentBulletInfo() //지금 불렛의 타입을 반환
{
	return currentBullet;
}