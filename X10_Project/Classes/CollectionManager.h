#pragma once

#include "Collection.h"
#include "StageScene.h"
//move to file system

///# 네임스페이스는 이런데 쓰라고 있는게 아니야~~~  이런 용도라면 enum을 쓰면 됨

///# 즉 이런식으로..
enum POS_IU
{
	PI_X = 100,
	PI_Y = 100
};


namespace POS_MONITOR
{
	const int X = 100;
	const int Y = 100;
}

namespace POS_BOTTLE
{
	const int X = 120;
	const int Y = 100;
}

namespace POS_SCARF
{
	const int X = 140;
	const int Y = 100;
}

namespace POS_SHOES
{
	const int X = 160;
	const int Y = 100;
}

namespace POS_LETTER
{
	const int X = 180;
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
