#include "stdafx.h"
#include "File.h"

extern const char* LastStageFile = "D:/X10/X10_Project/Resources/files/last_stage.txt";
extern const char* StageScene_Background_IMG_FILE = "res/starry_night.jpg";

int File::GetLastStage()
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

void File::UpdateLastStage(int stageNum)
{
	ofstream ofs(LastStageFile);
	ofs << (char)('0' + stageNum);
}
