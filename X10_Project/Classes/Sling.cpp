#include "stdafx.h"
#include "Sling.h"

Sling::Sling() : angle(0), power(0)
{
	Stick = Sprite::create("firework_stick 33x115.png");
	Stick->setPosition(200, 200);

	Shooter = Sprite::create("firework_shooter 6x67.png");
	Shooter->setPosition(200, 133);
}

void Sling::Shot()
{

}