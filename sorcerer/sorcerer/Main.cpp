#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "SpellBullet.h"
#include "hud.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main()
{
	// Window.
	sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Idiot sorcerer.", sf::Style::Default);
	Hud game_hud;

	// Clock.
	float deltaTime = 0.0f;
	sf::Clock clock;

	// Load the sprite.
	sf::Texture player_1_texture;
	player_1_texture.loadFromFile("Sprite\\player_1.png");
	sf::Texture player_2_texture;
	player_2_texture.loadFromFile("Sprite\\player_2.png");

	// World.
	sf::Texture dungeon_map;
	dungeon_map.loadFromFile("Sprite\\dungeon-map.png");
	sf::RectangleShape world;
	world.setSize(sf::Vector2f(512.0f, 512.0f));
	world.setOrigin(world.getSize() / 2.0f);
	world.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	world.setTexture(&dungeon_map);
	


	// Player 1 & Player 2.
	Player player_1(&player_1_texture, sf::Vector2u(3, 4), 2.0f,0.3f,200.0f,200.0f);
	player_1.SetInput(1);
	
	Player player_2(&player_2_texture, sf::Vector2u(3, 4), 2.0f, 0.3f, 400.0f, 400.0f);
	player_2.SetInput(2);
	
	// Spell bullet vector.
	std::vector<SpellBullet>::const_iterator iterator;
	std::vector<SpellBullet> bulletArray;

	// Bullet.
	SpellBullet bullet_1(2.0f);
	SpellBullet bullet_2(2.0f);
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	while (window.isOpen())
	{
		clock.restart().asSeconds();
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
		
		// Draw World and player.
		window.draw(world);
		game_hud.Draw(window);
		
		// Game loop.
		if (player_1.GetScore() < 4 && player_2.GetScore() < 4) {
			// Continue the game.
			if (player_1.GetHealth() > 0) {
				player_1.Draw(window);
			}
			else { game_hud.SetResultText(2); game_hud.DrawResultText(window); }
			if (player_2.GetHealth() > 0) {
				player_2.Draw(window);
			}
			else { game_hud.SetResultText(1); game_hud.DrawResultText(window); }
		}
		else {
			// Ending game.
			if (player_1.GetScore() == 4) {
				game_hud.SetResultText(3);
				game_hud.DrawResultText(window);
			}
			else if (player_2.GetScore() == 4) {
				game_hud.SetResultText(4);
				game_hud.DrawResultText(window);
			}
		}
		// Reset condition.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && (player_1.GetHealth() <= 0 || player_2.GetHealth() <= 0)) {
			if (player_1.GetHealth() > player_2.GetHealth()) {
				player_1.SetScore(player_1.GetScore() + 1); game_hud.ChangeScore(1, player_1.GetScore());
			} else  player_2.SetScore(player_2.GetScore() + 1); game_hud.ChangeScore(2, player_2.GetScore()); 
			
 			player_1.SetHealth(100);
			player_2.SetHealth(100);
		}

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
		window.display();
	}

	return 0;
}