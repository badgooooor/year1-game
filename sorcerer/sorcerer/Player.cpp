#include "Player.h"
#include "SpellBullet.h"

#include <iostream>
Player::Player(float deltaTime, float spawnX, float spawnY)
{
	// Initialize.
	speed = 5.0f;
	blinkDistance = 7.5f;
	this->deltaTime = deltaTime;

	health = 100;
	mana = 100;

	body.setSize(sf::Vector2f(30.0f, 45.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(spawnX, spawnY);

}

void Player::SetInput(int number)
{
	this->ControlSet = number;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	movement = sf::Vector2f(0.0f, 0.0f);
	// Keyboard Input.
	switch (ControlSet) {
		case 1:
			// WASD Movement.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * deltaTime; else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * deltaTime; else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * deltaTime; else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * deltaTime;

			// Blinking. NEED TO SET TIMER
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				xBlink = 0;	yBlink = 0;
				if (movement.x > 0) movement.x += blinkDistance;
				if (movement.x < 0) movement.x -= blinkDistance;
				if (movement.y > 0) movement.y += blinkDistance;
				if (movement.y < 0) movement.y -= blinkDistance;	
			} 

			break;
		case 2:
			// WASD Movement.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) movement.x -= speed * deltaTime; else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movement.x += speed * deltaTime; else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) movement.y -= speed * deltaTime; else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) movement.y += speed * deltaTime;

			// Blinking. NEED TO SET TIMER
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
				xBlink = 0;	yBlink = 0;
				if (movement.x > 0) movement.x += blinkDistance;
				if (movement.x < 0) movement.x -= blinkDistance;
				if (movement.y > 0) movement.y += blinkDistance;
				if (movement.y < 0) movement.y -= blinkDistance;
			}
			break;
	}

	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}