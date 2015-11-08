#include "stdafx.h"
#include "Sling.h"

Sling* Sling::instance = nullptr;

Sling* Sling::GetInstance()
{
	if (instance == nullptr)
		instance = new Sling();
	return instance;
}


