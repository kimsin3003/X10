#include "stdafx.h"
#include "FileStuff.h"

namespace FileStuff
{
	extern const char* LastStageFile = "../Resources/files/last_stage.txt";
	extern const char* StageScene_Background_IMG_FILE = "res/starry_night.jpg";
}

int FileStuff::GetLastStage()
{
	ifstream ifs(LastStageFile);
	char lastStage;
	while (!ifs.eof())
	{
		ifs.get(lastStage);
		cout << lastStage;
	}

	CCLOG("%cÀÔ´Ï´Ù", lastStage);
	ifs.close();
	return (int)(lastStage - '0');
}

void FileStuff::UpdateLastStage(int stageNum)
{
	if (GetLastStage() < stageNum)
	{
		ofstream ofs(LastStageFile);
		ofs << (char)('0' + stageNum);
	}
}
