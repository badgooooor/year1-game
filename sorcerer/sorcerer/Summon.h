#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"
#include "Animation.h"
class Summon
{
public:
	Summon::Summon(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Summon();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	Collider GetCollider() { return Collider(body); }
	bool GetExploded() { return exploded; }
	void SetExploded(bool exploded) { this->exploded = exploded; }

	unsigned int GetPlayerSkill() { return playerSkill; }
	void SetPlayerSkill(unsigned int playerSkill) { this->playerSkill = playerSkill; }
public:

private:
	sf::RectangleShape body;
	sf::Texture texture;
	float deltaTime;

	Animation animation;
	unsigned int row;
	sf::Vector2u textureSize;

	unsigned int playerSkill;
	bool exploded;

private:
};

