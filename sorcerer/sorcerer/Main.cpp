#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "SpellBullet.h"
int main()
{
	// Player 1 & Player 2.
	Player player_1(0.3f,200.0f,200.0f);
	player_1.SetInput(1);

	Player player_2(0.3f, 200.0f, 200.0f);
	player_2.SetInput(2);
	
	sf::RenderWindow window(sf::VideoMode(800, 600),"Hello SFML", sf::Style::Default);
	
	// Spell bullet vector.
	std::vector<SpellBullet>::const_iterator iterator;
	std::vector<SpellBullet> bulletArray;


	// Bullet.
	SpellBullet bullet_1(2.0f);
	SpellBullet bullet_2(2.0f);
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(200, 200);
	text.setString("Somewhat collision test");
	while (window.isOpen())
	{
		window.setFramerateLimit(60);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		
		// Debug on console.

		// Firing.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			bullet_1.direction = player_1.GetMovement();
			sf::Vector2f bullet_position_1(player_1.GetPosition().x + (bullet_1.direction.x * 6.0f), player_1.GetPosition().y + (bullet_1.direction.y * 6.0f));
			bullet_1.SetPosition(bullet_position_1);			// Need mod the position.
			bulletArray.push_back(bullet_1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
			bullet_2.direction = player_2.GetMovement();
			sf::Vector2f bullet_position_2(player_2.GetPosition().x + (bullet_2.direction.x * 6.0f), player_2.GetPosition().y + (bullet_2.direction.y * 6.0f));
			bullet_2.SetPosition(bullet_position_2);			// Need mod the position.
			bulletArray.push_back(bullet_2);
		}
		
		// Collision and update.
		player_1.Update(1.0f);
		player_1.GetCollider().checkCollision(player_2.GetCollider(), 0.1f);
		
		player_2.Update(1.0f);
		player_2.GetCollider().checkCollision(player_1.GetCollider(), 0.1f);
		
		// Draw
		if (player_1.GetHealth() > 0) player_1.Draw(window);
		if (player_2.GetHealth() > 0) player_2.Draw(window);

		// Set Bullet.
		int counter = 0;
		for (iterator = bulletArray.begin(); iterator != bulletArray.end(); iterator++) {
			bulletArray[counter].Update(0.25f);
			if (bulletArray[counter].GetCollider().checkCollision(player_2.GetCollider(), 0.1f)) {
				player_2.SetHealth(player_2.GetHealth() - 1);
				std::cout << "Player 2 's health : " << player_2.GetHealth() << std::endl;
				bulletArray[counter].SetShot(false);
			} else if (bulletArray[counter].GetCollider().checkCollision(player_1.GetCollider(), 0.1f)) {
				player_1.SetHealth(player_1.GetHealth() - 1);
				std::cout << "Player 1 's health : " << player_1.GetHealth() << std::endl;
				bulletArray[counter].SetShot(false);
			} 
			if(!bulletArray[counter].GetShot()) {
				window.draw(bulletArray[counter].body);
			}
			counter++;
		}

		window.draw(text);
		window.display();
	}

	return 0;
}