#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "SpellBullet.h"
#include "Animation.h"

class Player
{
public:
	Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float deltaTime, float spawnX, float spawnY);
	~Player();

	void SetInput(int number) { this->ControlSet = number; }
	void SetTexture(sf::Texture* texture) { body.setTexture(texture); }
	void SetTextureRect(sf::Vector2u textureRect) { body.setTextureRect(sf::IntRect(textureRect.x * 2, textureRect.y * 2, textureRect.x, textureRect.y)); }
	void SetTextureRect(sf::IntRect uvRect) { body.setTextureRect(uvRect); }
	
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void DrawHealthBar(float currentHealth, float maxHealth);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetMovement() { return movement; }
	sf::Vector2f GetSize() { return sf::Vector2f(body.getSize().x, body.getSize().y); }
	sf::Vector2f GetHalfSize() { return sf::Vector2f(body.getSize().x / 2, body.getSize().y / 2); }
	
	Collider GetCollider() { return Collider(body); }

	float GetHealth() { return health; }
	void SetHealth(float health) { this->health = health; }

	float GetMana() { return mana; }
	void SetMana(float mana) { this->mana = mana; }

	unsigned int GetScore() { return score; }
	void SetScore(unsigned int score) { this->score = score; }

public:
	sf::Color debugColor;

private:
	sf::RectangleShape body;

	Animation animation;
	unsigned int row;
	sf::Vector2u textureSize;

	int ControlSet;
	float speed;
	float deltaTime;
	sf::Vector2f movement;

	float blinkDistance;
	float xBlink;
	float yBlink;
	
	sf::RectangleShape currentHealthBar;
	sf::RectangleShape maxHealthBar;
	float health;
	float mana;

	unsigned int score;
};

