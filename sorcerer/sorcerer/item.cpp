#include "item.h"
#include <iostream>



Item::Item(float spawnX, float spawnY) {
	// Random item.
	item_id = (rand() % 3) + 1;
	std::cout << "Item number : " << item_id << std::endl;

	// Load texture.
	health_potion.loadFromFile("Sprite\\item_health_potion.png");
	mana_potion.loadFromFile("Sprite\\item_mana_potion.png");
	skill_scroll.loadFromFile("Sprite\\item_scroll.png");

	// Initialize the body.
	body.setPosition(spawnX, spawnY);
	body.setSize(sf::Vector2f(16.0f, 16.0f));
	body.setOrigin(body.getSize() / 2.0f);
}

Item::~Item()
{
}

void Item::Update() {
	switch (item_id) {
		case 1:
			body.setTexture(&health_potion);
			break;
		case 2:
			body.setTexture(&mana_potion);
			break;
		case 3:
			body.setTexture(&skill_scroll);
			break;
	}
}

void Item::Draw(sf::RenderWindow & window) {
	window.draw(body);
}

void Item::randomItem() {
	float randomX = (rand() % 450) + 200;
	float randomY = (rand() % 450) + 200;
	item_id = (rand() % 3) + 1;
	body.setPosition(sf::Vector2f(randomX, randomY));
	std::cout << "Item respawn at " << randomX << "," << randomY << std::endl;
}
