#include "GameObject.h"

BINI::GameObject::GameObject(BINI::Renderer* renderer, std::string path)
{
	gTexture = new Texture(renderer, path);
}

BINI::GameObject::~GameObject()
{
	if (gTexture != NULL)
	{
		delete gTexture;
		gTexture = NULL;
	}
}

void BINI::GameObject::draw(BINI::Renderer* renderer, int x, int y)
{
	gTexture->render(renderer, x, y);
}