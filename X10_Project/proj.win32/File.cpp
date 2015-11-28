#include "stdafx.h"
#include "File.h"
#include <iostream>
#include <fstream>


int File::GetLastStage()
{
	ifstream ifs(LastStageFile);
	char lastStage;
	while (!ifs.eof())
	{
		ifs.get(lastStage);
		cout << lastStage;
	}
	ifs.close();
	return (int)(lastStage - '0');
}

void File::UpdateLastStage(int stageNum)
{
	ofstream ofs(LastStageFile);
	ofs << '0' + stageNum;
}
