#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	unsigned int GetRow() { return row; }
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

	bool GetHealHealth() { return item_heal; }
	void SetHealHealth(bool item_heal) { this->item_heal = item_heal; }

	bool GetHealMana() { return item_mana; }
	void SetHealMana(bool item_mana) { this->item_mana = item_mana; }

	bool GetScroll() { return item_scroll; }
	void SetScroll(bool item_scroll) { this->item_scroll = item_scroll; }

	bool GetMine() { return item_mine; }
	void SetMine(bool item_mine) { this->item_mine = item_mine; }
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

	bool item_heal;
	bool item_mana;
	bool item_scroll;
	bool item_mine;

	unsigned int score;

	sf::Clock clock;
	sf::Time time;
	sf::Time slowTime = sf::seconds(2);
	sf::Time freezeTime = sf::seconds(4);
	sf::Time burnTime = sf::seconds(4);
	sf::Time burnDamageTime = sf::milliseconds(500);
	sf::Time regenTime = sf::seconds(5);

	sf::Music status_burned;
	sf::Music status_freezed;
};