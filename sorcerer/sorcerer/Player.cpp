#include "Player.h"
#include "SpellBullet.h"

#include <iostream>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float deltaTime, float spawnX, float spawnY) 
	: animation(texture, imageCount, switchTime)
{
	// Initialize for player.
	speed = 5.0f;
	blinkDistance = 7.5f;
	this->deltaTime = deltaTime;
	row = 0;

	health = 100;
	mana = 100;

	body.setSize(sf::Vector2f(30.0f, 45.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(spawnX, spawnY);
	body.setTexture(texture);

	Animation animation(texture, imageCount, switchTime);
	textureSize = texture->getSize();
	textureSize.x /= 3;
	textureSize.y /= 4;
	
	// Initialize for health bar.
	maxHealthBar.setSize(sf::Vector2f(45.0f, 3.0f));
	maxHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	maxHealthBar.setOrigin(maxHealthBar.getSize() / 2.0f);
	maxHealthBar.setFillColor(sf::Color::White);

	currentHealthBar.setSize(sf::Vector2f(45.0f, 3.0f));
	currentHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	currentHealthBar.setOrigin(maxHealthBar.getSize() / 2.0f);
	currentHealthBar.setFillColor(sf::Color::Red);
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				movement.x -= speed * deltaTime; row = 1;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				movement.x += speed * deltaTime; row = 2;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { 
				movement.y -= speed * deltaTime; row = 3; 
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				movement.y += speed * deltaTime; row = 0;
			}

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				movement.x -= speed * deltaTime; row = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				movement.x += speed * deltaTime; row = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				movement.y -= speed * deltaTime; row = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				movement.y += speed * deltaTime; row = 0;
			}

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

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	
	// Update the health bar position.
	maxHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	currentHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	currentHealthBar.setSize(sf::Vector2f((health / 100) * maxHealthBar.getSize().x, maxHealthBar.getSize().y));
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(maxHealthBar);
	window.draw(currentHealthBar);
}

void Player::DrawHealthBar(float currentHealth, float maxHealth)
{

}
