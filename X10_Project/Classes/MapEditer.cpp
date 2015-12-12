#include "stdafx.h"
#include "MapEditer.h"
#include "MapEditLayer.h"
#include "StageInformation.h"

Scene* MapEditer::createScene()
{
	Scene* scene = Scene::create();

	MapEditer* layer = MapEditer::create();

	scene->addChild(layer);

	return scene;
}

bool MapEditer::init()
{
	m_layer = Layer::create();

	return true;
}

void MapEditer::SetCallBackFuncs(){

}
