#pragma once

class Collection : public Node
{
public:
	CREATE_FUNC(Collection);
	bool init();
	void SetSprite(const string& name, const Point& pos);

private:
	Sprite* m_spr;
};