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

	unsigned int GetSkill() { return skill; }
	void SetSkill(unsigned int skill) { this->skill = skill; }

	unsigned int GetScore() { return score; }
	void SetScore(unsigned int score) { this->score = score; }

	bool GetFire() { return on_fire; }
	void SetFire(bool on_fire) { this->on_fire = on_fire; }

	bool GetFreeze() { return on_freeze; }
	void SetFreeze(bool on_freeze) { this->on_freeze = on_freeze; }

	bool GetSlow() { return on_slowed; }
	void SetSlow(bool on_slowed) { this->on_slowed = on_slowed; }

	float GetSpeed() { return speed; }
	void SetSpeed(float speed) { this->speed = speed; }
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
	sf::RectangleShape currentManaBar;
	sf::RectangleShape maxManaBar;

	float health;
	float mana;

	unsigned int skill;
	bool on_fire;
	bool on_freeze;
	bool on_slowed;

	unsigned int score;

	sf::Clock clock;
	sf::Time time;
	sf::Time slowTime = sf::seconds(2);
	sf::Time freezeTime = sf::seconds(4);
	sf::Time burnTime = sf::seconds(4);
	sf::Time burnDamageTime = sf::milliseconds(500);
};