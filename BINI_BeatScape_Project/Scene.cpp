#include "Scene.h"

BINI::Scene::Scene()
{
	transitionState = false;
}

BINI::Scene::~Scene()
{
	transitionState = false;
}

bool BINI::Scene::isTransitioning()
{
	return transitionState;
}

void BINI::Scene::willTransition()
{
	transitionState = true;
}