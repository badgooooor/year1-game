#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "SpellBullet.h"
#include "Animation.h"

class Player
{
public:
	Player::Player(float deltaTime, float spawnX, float spawnY);
	void SetInput(int number);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetMovement() { return movement; }
	sf::Vector2f GetSize() { return sf::Vector2f(body.getSize().x, body.getSize().y); }
	sf::Vector2f GetHalfSize() { return sf::Vector2f(body.getSize().x / 2, body.getSize().y / 2); }
	
	Collider GetCollider() { return Collider(body); }

	float GetHealth() { return health; }
	void SetHealth(float health) { this->health = health; }

	float GetMana() { return mana; }
	void SetMana(float mana) { this->mana = mana; }

	sf::Color debugColor;

private:
	sf::RectangleShape body;

	int ControlSet;
	float speed;
	float deltaTime;
	sf::Vector2f movement;

	float blinkDistance;
	float xBlink;
	float yBlink;

	float health;
	float mana;
};

