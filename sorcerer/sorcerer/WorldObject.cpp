#include "WorldObject.h"



WorldObject::WorldObject()
{
	randomPosition();
	objectId = (rand() % 4) + 1;
	
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setOrigin(body.getSize() / 2.0f);
}


WorldObject::~WorldObject()
{
}

void WorldObject::Update()
{
	switch (objectId) {
		case 1: worldObject.loadFromFile("Sprite\\world_box_1.png"); break;
		case 2: worldObject.loadFromFile("Sprite\\world_box_2.png"); break; 
		case 3: worldObject.loadFromFile("Sprite\\world_wood_1.png"); break;
		case 4: worldObject.loadFromFile("Sprite\\world_wood_2.png"); break;
	}
	body.setTexture(&worldObject);
}

void WorldObject::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void WorldObject::randomPosition()
{
	float randomX = (rand() % 450) + 200;
	float randomY = (rand() % 450) + 200;
	objectId = (rand() % 4) + 1;
	body.setPosition(sf::Vector2f(randomX, randomY));
}
