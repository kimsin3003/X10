#pragma once

class Collection : public Node
{
public:
	CREATE_FUNC(Collection);
	bool init();
	void SetCollection(const string& name, const Point& pos, int code);
	MenuItemImage* GetCollection() { return m_collection; }
	static bool m_isLooking;

private:
	MenuItemImage* m_collection;
	Sprite* m_collSpr;
	Sprite* m_textBox;
	Label* m_text;

	void MakeTextBox(const string& name, int code);
	void LetterExplanation();
	void MonitorExplanation();
	void BottleExplanation();
	void ScarfExplanation();
	void ShoesExplanation();
	void EndLooking() { m_isLooking = false; }

	enum CONFIG
	{
		TEXT_POS = 30,
	};
};