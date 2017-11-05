#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"
class WorldObject
{
public:
	WorldObject();
	~WorldObject();

	void Update();
	void Draw(sf::RenderWindow &window);

	void randomPosition();

	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	
	sf::Texture worldObject;

	unsigned int objectId;
};

