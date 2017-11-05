#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"

class Item
{
public:
	Item(float spawnX, float spawnY);
	~Item();

	void Update();
	void Draw(sf::RenderWindow &window);
	
	void randomItem();
	// Sender, Getter.
	unsigned int GetItemId() { return item_id; }
	void SetItemId(unsigned int item_id) { this->item_id = item_id; }

	Collider GetCollider() { return Collider(body); }

private:
	sf::Texture health_potion;
	sf::Texture mana_potion;
	sf::Texture skill_scroll;
	sf::Texture arcane_ball;
	sf::RectangleShape body;

	// 1-Health potion 2-Mana potion 3-Scroll of randomness.
	unsigned int item_id;

};

