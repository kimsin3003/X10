#pragma once

class GameManager
{
public:
	GameManager* GetInstance();

private:
	GameManager* instance;
	GameManager();
	~GameManager();

};
