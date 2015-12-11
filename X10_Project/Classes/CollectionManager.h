#pragma once

#include "Collection.h"
#include "StageScene.h"

class CollectionManager
{
public:
	CollectionManager();
	~CollectionManager() { m_collections.clear(); }
	void InitCollections(int stageNumber);
	void ResetCollections();
	void AppendCollectionToLayer(StageScene* layer);
	Sprite* GetCollectionSprOfStage(int stageNum);

//  When the collection touched, run the interactions 

//	void SetEffectToCharacter(//Chractor* character);
//  void ShowBoxOfTheCollection(//Collection* collection);

private:
	Vector<Collection*> m_collections;
	int m_curColNum;
	Point m_colPos;
	Point m_deltaPos;

	enum CollectionCode
	{
		SHOES = 1,
		SCARF = 4,
		BOTTLE = 8,
		MONITOR = 11,
		LETTER = 14
	};
};
