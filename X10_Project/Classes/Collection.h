#pragma once

class Collection : public Node
{
public:
	CREATE_FUNC(Collection);
	bool init();
	void SetCollection(const string& name, const Point& pos, int code);
	MenuItemImage* GetCollection() { return m_collection; }

private:
	MenuItemImage* m_collection;

	void LetterExplanation();
	void MonitorExplanation();
	void BottleExplanation();
	void ScarfExplanation();
	void ShoesExplanation();
};