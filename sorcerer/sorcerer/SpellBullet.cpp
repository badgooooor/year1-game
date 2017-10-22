#include "SpellBullet.h"

SpellBullet::SpellBullet(float speed)
{
	body.setSize(sf::Vector2f(10.0f, 10.0f));
	body.setFillColor(sf::Color::Green);
	this->speed = speed;
}

SpellBullet::~SpellBullet()
{
}


void SpellBullet::Update(float deltaTime) {
	if (direction.x == 0 && direction.y == 0) {
		movement.x = lastestDirection.x * speed * deltaTime;
		movement.y = lastestDirection.y * speed * deltaTime;
	}
	else {
		lastestDirection.x = direction.x;
		lastestDirection.y = direction.y;
		movement.x += direction.x * speed * deltaTime;
		movement.y += direction.y * speed * deltaTime;
	}
	body.move(movement);
}

void SpellBullet::Draw(sf::RenderWindow& window) {
		window.draw(body); 
}

void SpellBullet::SetPosition(sf::Vector2f position) {
	body.setPosition(position);
}
