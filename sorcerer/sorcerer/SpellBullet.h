#pragma once
#include <SFML/Graphics.hpp>
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

private:
	sf::Vector2f movement;
	sf::Vector2f lastestDirection;
	float speed;
	float deltaTime;

	bool shot;
};

