#include "SpellBullet.h"
#include <iostream>
SpellBullet::SpellBullet(float speed)
{

	body.setSize(sf::Vector2f(10.0f, 10.0f));
	body.setFillColor(sf::Color::Green);
	this->speed = speed;
	shot = true;
}

SpellBullet::~SpellBullet()
{
}


void SpellBullet::Update(float deltaTime) {
	// Set color for each player.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
		if (playerSkill > 0 && playerSkill <= 5) {
			body.setFillColor(sf::Color::Red);
		} else if (playerSkill > 5 && playerSkill <= 10) {
			body.setFillColor(sf::Color::Blue);
		} else if (playerSkill > 10 && playerSkill <= 15) {
			body.setFillColor(sf::Color::Yellow);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
			body.setFillColor(sf::Color::Green);
		}
	}
	time = clock.getElapsedTime();
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
	if (time.asSeconds() > lifetime.asSeconds()) shot = false;
}

void SpellBullet::Draw(sf::RenderWindow& window) {
	if(GetShot()) window.draw(body);
}

void SpellBullet::SetPosition(sf::Vector2f position) {
	body.setPosition(position);
}
