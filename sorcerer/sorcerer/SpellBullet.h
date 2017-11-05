#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collision.h"
class SpellBullet
{
public:
	SpellBullet(float speed);
	~SpellBullet();
	
	void Update(float deltaTime);
	void SetPosition(sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
	
	sf::Vector2f direction;
	sf::RectangleShape body;

	Collider GetCollider() { return Collider(body); }

	bool GetShot() { return shot; }
	void SetShot(bool shot) { this->shot = shot; }

	unsigned int GetPlayerSkill() { return playerSkill; }
	void SetPlayerSkill(unsigned int playerSkill) { this->playerSkill = playerSkill; }

	unsigned int SetDir(unsigned int dir) { this->dir = dir; }
	sf::Color GetColor() { return body.getFillColor(); }
private:
	sf::Texture texture;
	
	sf::Vector2f movement;
	sf::Vector2f lastestDirection;
	unsigned int dir;
	float speed;
	float deltaTime;

	sf::Clock clock;
	sf::Time time;
	sf::Time lifetime = sf::seconds(5);
	bool shot;

	bool isMine;
	unsigned int playerSkill;
};

