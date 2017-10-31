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

	skill = (rand() % 15) + 1;

	std::cout << skill << std::endl;
	body.setSize(sf::Vector2f(30.0f, 45.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(spawnX, spawnY);
	body.setTexture(texture);

	Animation animation(texture, imageCount, switchTime);
	textureSize = texture->getSize();
	textureSize.x /= 3;
	textureSize.y /= 4;
	
	// Initialize for health bar and mana bar.
	maxHealthBar.setSize(sf::Vector2f(45.0f, 3.0f));
	maxHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	maxHealthBar.setOrigin(maxHealthBar.getSize() / 2.0f);
	maxHealthBar.setFillColor(sf::Color::White);

	currentHealthBar.setSize(sf::Vector2f(45.0f, 3.0f));
	currentHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	currentHealthBar.setOrigin(maxHealthBar.getSize() / 2.0f);
	currentHealthBar.setFillColor(sf::Color::Red);

	maxManaBar.setSize(sf::Vector2f(45.0f, 3.f));
	maxManaBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	maxManaBar.setOrigin(maxManaBar.getSize() / 2.0f);
	maxManaBar.setFillColor(sf::Color::White);

	currentManaBar.setSize(sf::Vector2f(45.0f, 3.f));
	currentManaBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	currentManaBar.setOrigin(maxManaBar.getSize() / 2.0f);
	currentManaBar.setFillColor(sf::Color::Blue);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	movement = sf::Vector2f(0.0f, 0.0f);
	// Keyboard Input.
	if (on_freeze && !on_fire) {
		// Freeze the player.
		body.setFillColor(sf::Color::Blue);
		time = clock.getElapsedTime();
		if (time.asSeconds() >= freezeTime.asSeconds()) {
			time = clock.restart();
			on_freeze = false;
		}
	} else {
		// Slow effect.
		if (on_slowed) {
			body.setFillColor(sf::Color::Yellow);
			time = clock.getElapsedTime();
			speed = 2.0f;
			if (time.asSeconds() >= slowTime.asSeconds()) {
				time = clock.restart();
				speed = 5.0f;
				on_slowed = false;
			}
		} else body.setFillColor(sf::Color::White);
		switch (ControlSet) {
		case 1:
			// WASD Movement.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				movement.x -= speed * deltaTime; row = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				movement.x += speed * deltaTime; row = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				movement.y -= speed * deltaTime; row = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				movement.y += speed * deltaTime; row = 0;
			}

			// Blinking. NEED TO SET TIMER
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mana >= 10) {
				xBlink = 0;	yBlink = 0; SetMana(GetMana() - 5.0f);
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && mana >= 10 && movement.x != 0 && movement.y != 0) {
				xBlink = 0;	yBlink = 0; SetMana(GetMana() - 5.0f);
				if (movement.x > 0) movement.x += blinkDistance;
				if (movement.x < 0) movement.x -= blinkDistance;
				if (movement.y > 0) movement.y += blinkDistance;
				if (movement.y < 0) movement.y -= blinkDistance;
			}
			break;
		}
	}
	// On Fire, continuous damage to player who get burned.
	if (on_fire) {
		body.setFillColor(sf::Color::Red);
		time = clock.getElapsedTime();
		SetHealth(GetHealth() - 0.05f);
		if (time.asSeconds() >= burnTime.asSeconds()) {
			body.setFillColor(sf::Color::White);
			time = clock.restart();
			on_fire = false;
		}
	}
	// Mana regeneration.
	if(GetMana() < 100.0f) SetMana(GetMana() + 0.5f);

	// Animation and update the position.
	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	
	// Update the health bar and mana bar.
	maxHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	currentHealthBar.setPosition(body.getPosition().x, body.getPosition().y - 23.0f);
	currentHealthBar.setSize(sf::Vector2f((health / 100) * maxHealthBar.getSize().x, maxHealthBar.getSize().y));
	maxManaBar.setPosition(body.getPosition().x, body.getPosition().y - 21.5f);
	currentManaBar.setPosition(body.getPosition().x, body.getPosition().y - 21.5f);
	currentManaBar.setSize(sf::Vector2f((mana / 100) * maxManaBar.getSize().x, maxManaBar.getSize().y));

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(maxHealthBar);
	window.draw(currentHealthBar);
	window.draw(maxManaBar);
	window.draw(currentManaBar);
}

void Player::DrawHealthBar(float currentHealth, float maxHealth)
{

}