#pragma once

#include "Collection.h"
#include "StageScene.h"

//move to file system
namespace POS_MONITOR
{
	const int X = 100;
	const int Y = 100;
}

namespace POS_BOTTLE
{
	const int X = 125;
	const int Y = 100;
}

namespace POS_SCARF
{
	const int X = 150;
	const int Y = 100;
}

namespace POS_SHOES
{
	const int X = 175;
	const int Y = 100;
}

namespace POS_LETTER
{
	const int X = 200;
	const int Y = 100;
}

class CollectionManager
{
public:
	CollectionManager();
	~CollectionManager() { m_collections.clear(); }
	void InitCollections(int stageNumber);
	void ResetCollections();
	void AppendCollectionToLayer(StageScene* layer);
	Sprite* GetCollectionSprOfStage(int stageNum);

//  When a collection touched, run interactions 

//	void SetEffectToCharacter(//Chractor* character);
//  void ShowBoxOfTheCollection(//Collection* collection);

private:
	Vector<Collection*> m_collections;
	int m_curColNum;
	/*	0	1	2	3	4	*/
   //  	LE  SH  SC  BO  MO	
	enum CollectionCode
	{
		LETTER = 1,
		SHOES = 2,
		SCARF = 3,
		BOTTLE = 4,
		MONITOR = 5
	};
};
