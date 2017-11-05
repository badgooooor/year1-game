#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include "SpellBullet.h"
#include "hud.h"
#include "item.h"
#include "WorldObject.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

unsigned int state = 0;
void play(sf::RenderWindow &window);
void main_menu(sf::RenderWindow &window);

int main() {
	// Window.
	sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Idiot sorcerer.", sf::Style::Default);
	main_menu(window);
	return 0;
}

// Main menu.
void main_menu(sf::RenderWindow &window) {
	sf::Music music;
	music.openFromFile("Sound\\main_menu.ogg");
	music.setLoop(true);
	music.play();
	
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/ARCADECLASSIC.ttf");
	sf::Font title_font;
	title_font.loadFromFile("C:/Windows/Fonts/ARCADECLASSIC.tff");
	// Background image.
	sf::Texture background_image;
	background_image.loadFromFile("Sprite/main_bg.png");

	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_HEIGHT, WINDOW_WIDTH));
	background.setTexture(&background_image);
	
	sf::RectangleShape title;
	sf::Texture title_pic;
	title_pic.loadFromFile("Sprite\\title.png");
	title.setTexture(&title_pic);
	title.setSize(sf::Vector2f(500.0f, 200.0f));
	title.setOrigin(title.getSize() / 2.0f);
	title.setPosition(sf::Vector2f(400.0f, 400.0f));

	sf::Text sub_heading;
	sub_heading.setFont(font);
	sub_heading.setString("By Yuttakhan Baingen 60010842");
	sub_heading.setCharacterSize(24);
	sub_heading.setFillColor(sf::Color::White);
	sub_heading.setPosition(220, 450);

	sf::Text start_text;
	start_text.setFont(font);
	start_text.setString("S  is  for  start");
	start_text.setCharacterSize(24);
	start_text.setFillColor(sf::Color::Green);
	start_text.setPosition(320, 500);

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			state = 1;
		}
		if (state == 1) { 
			music.stop();
			play(window); 
		}
		window.clear();
		window.draw(background);
		window.draw(title);
		window.draw(sub_heading);
		window.draw(start_text);

		window.display();
	}
}

// Play screen.
void play(sf::RenderWindow &window) {
	srand(time(NULL));
	
	// Initialize the objects.
	// HUD.
	Hud game_hud;
	
	// Music
	sf::Music music;
	music.setVolume(30);
	music.openFromFile("Sound\\fight_theme.ogg");
	music.setLoop(true);
	music.play();
	
	// Sound Effect.
	sf::Music item_grab;
	item_grab.openFromFile("Sound\\item_grab.wav");
	sf::Music fire_sound;
	sf::Music slow_sound;
	sf::Music ice_sound;
	sf::Music bullet_shoot;
	fire_sound.openFromFile("Sound\\skill_fire.ogg");
	slow_sound.openFromFile("Sound\\skill_slow.ogg");
	ice_sound.openFromFile("Sound\\skill_ice.ogg");
	bullet_shoot.openFromFile("Sound\\magic_bullet.ogg");
	
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

	WorldObject object_1;
	WorldObject object_2;
	WorldObject object_3;

	// Player 1 & Player 2.
	Player player_1(&player_1_texture, sf::Vector2u(3, 4), 2.0f, 0.3f, 200.0f, 200.0f);
	player_1.SetInput(1);

	Player player_2(&player_2_texture, sf::Vector2u(3, 4), 2.0f, 0.3f, 600.0f, 600.0f);
	player_2.SetInput(2);

	// Spell bullet vector.
	std::vector<SpellBullet>::const_iterator iterator;
	std::vector<SpellBullet> bulletArray;

	// Bullet.
	SpellBullet bullet_1(2.0f);
	SpellBullet bullet_2(2.0f);
	bullet_1.SetPlayerSkill(player_1.GetSkill());
	bullet_2.SetPlayerSkill(player_2.GetSkill());

	// Item.
	Item item(400.0f,400.0f);

	// Font.
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	// Game Loop.
	clock.restart().asSeconds();
	window.setFramerateLimit(60);
	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();

		// Firing for player 1.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			bullet_shoot.play();
			bullet_1.direction = player_1.GetMovement();
			sf::Vector2f bullet_position_1(player_1.GetPosition().x + (bullet_1.direction.x * 10.0f), player_1.GetPosition().y + (bullet_1.direction.y * 10.0f));
			bullet_1.SetPosition(bullet_position_1);			
			bulletArray.push_back(bullet_1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && player_1.GetMana() > 0) {
			switch (player_1.GetSkill()) {
			case 1: fire_sound.play(); break;
			case 2: ice_sound.play(); break;
			case 3: slow_sound.play(); break;
			}
			bullet_1.direction = player_1.GetMovement();
			sf::Vector2f bullet_position_1(player_1.GetPosition().x + (bullet_1.direction.x * 10.0f), player_1.GetPosition().y + (bullet_1.direction.y * 10.0f));
			bullet_1.SetPosition(bullet_position_1);
			bulletArray.push_back(bullet_1);
			if (player_1.GetSkill() != 4) {
				player_1.SetMana(player_1.GetMana() - 10.0f);
				sf::Vector2f bullet_position_1(player_1.GetPosition().x + (bullet_1.direction.x * 10.0f), player_1.GetPosition().y + (bullet_1.direction.y * 10.0f));
				bullet_1.SetPosition(bullet_position_1);
			} else {
				player_1.SetMana(player_1.GetMana() - 30.0f);
				sf::Vector2f bullet_position_1(player_1.GetPosition().x + (bullet_1.direction.x * 20.0f), player_1.GetPosition().y + (bullet_1.direction.y * 20.0f));
				bullet_1.SetPosition(bullet_position_1);
			}
		}

		// Firing for player 2.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
			bullet_shoot.play();
			bullet_2.direction = player_2.GetMovement();
			sf::Vector2f bullet_position_2(player_2.GetPosition().x + (bullet_2.direction.x * 10.0f), player_2.GetPosition().y + (bullet_2.direction.y * 10.0f));
			bullet_2.SetPosition(bullet_position_2);			
			bulletArray.push_back(bullet_2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && player_2.GetMana() > 0) {
			switch (player_2.GetSkill()) {
			case 1: fire_sound.play(); break;
			case 2: ice_sound.play(); break;
			case 3: slow_sound.play(); break;
			}
			bullet_2.direction = player_2.GetMovement();
			bulletArray.push_back(bullet_2);
			if (player_2.GetSkill() != 4) {
				player_2.SetMana(player_2.GetMana() - 10.0f);
				sf::Vector2f bullet_position_2(player_2.GetPosition().x + (bullet_2.direction.x * 10.0f), player_2.GetPosition().y + (bullet_2.direction.y * 10.0f));
				bullet_2.SetPosition(bullet_position_2);
			}
			else {
				player_2.SetMana(player_2.GetMana() - 30.0f);
				sf::Vector2f bullet_position_2(player_2.GetPosition().x + (bullet_2.direction.x * 20.0f), player_2.GetPosition().y + (bullet_2.direction.y * 20.0f));
				bullet_2.SetPosition(bullet_position_2);
			}
		}
		// Collision and update.
		player_1.Update(1.0f);
		player_1.GetCollider().checkCollision(player_2.GetCollider(), 0.1f);

		player_2.Update(1.0f);
		player_2.GetCollider().checkCollision(player_1.GetCollider(), 0.1f);

		// Draw World and player.
		window.draw(world);
		object_1.Draw(window);
		object_2.Draw(window);
		object_3.Draw(window);
		game_hud.Draw(window);

		object_1.Update();
		object_2.Update();
		object_3.Update();
		item.Update();
		item.Draw(window);

		// Game loop.
		if (player_1.GetScore() < 4 && player_2.GetScore() < 4) {
			// Continue the game.
			if (player_1.GetHealth() > 0) {
				player_1.Draw(window);
			} else { game_hud.SetResultText(2); game_hud.DrawResultText(window); }
			if (player_2.GetHealth() > 0) {
				player_2.Draw(window);
			} else { game_hud.SetResultText(1); game_hud.DrawResultText(window); }
			player_1.SetSkill((rand() % 3) + 1); player_2.SetSkill((rand() % 3) + 1);
		} else {
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

		// Collision with item & player.
		player_1.GetCollider().checkCollision(object_1.GetCollider(), 0.0f);
		player_1.GetCollider().checkCollision(object_2.GetCollider(), 0.0f);
		player_1.GetCollider().checkCollision(object_3.GetCollider(), 0.0f);
		player_2.GetCollider().checkCollision(object_1.GetCollider(), 0.0f);
		player_2.GetCollider().checkCollision(object_2.GetCollider(), 0.0f);
		player_2.GetCollider().checkCollision(object_3.GetCollider(), 0.0f);
		// Item Grabbing.
		if (item.GetCollider().checkCollision(player_1.GetCollider(), 0.0f)) {
			if (item.GetItemId() == 1) {
				item_grab.play();
				player_1.SetHealHealth(true);
			} else if (item.GetItemId() == 2) {
				item_grab.play();
				player_1.SetHealMana(true);
			} else if (item.GetItemId() == 3) {
				item_grab.play();
				player_1.SetScroll(true);
				bullet_1.SetPlayerSkill(player_1.GetSkill());
				std::cout << bullet_1.GetPlayerSkill() << std::endl;
			} else if (item.GetItemId() == 4) {
				player_1.SetMine(true);
			}
			item.randomItem();
		}
		if (item.GetCollider().checkCollision(player_2.GetCollider(), 0.0f)) {
			if (item.GetItemId() == 1) {
				item_grab.play();
				player_2.SetHealHealth(true);
			} else if (item.GetItemId() == 2) {
				item_grab.play();
				player_2.SetHealMana(true);
			} else if (item.GetItemId() == 3) {
				item_grab.play();
				player_2.SetScroll(true);
				bullet_2.SetPlayerSkill(player_2.GetSkill());
				std::cout << bullet_2.GetPlayerSkill() << std::endl;
			} else if (item.GetItemId() == 4) {
				player_2.SetMine(true);
			}
			item.randomItem();
		}

		// Set Bullet + Damaging.
		int counter = 0;
		for (iterator = bulletArray.begin(); iterator != bulletArray.end(); iterator++) {
			bulletArray[counter].Update(0.25f);
			if (bulletArray[counter].GetCollider().checkCollision(player_2.GetCollider(), 0.1f)) {
				if (bulletArray[counter].GetColor() == sf::Color::Red) {
					player_2.SetFire(true); 
				} else if (bulletArray[counter].GetColor() == sf::Color::Blue) {
					player_2.SetFreeze(true); 
				} else if (bulletArray[counter].GetColor() == sf::Color::Yellow) {
					player_2.SetSlow(true);
				} else if (bulletArray[counter].GetColor() == sf::Color::Green) {
					player_2.SetHealth(player_2.GetHealth() - 1);
				}
				std::cout << "Player 2 's health : " << player_2.GetHealth() << std::endl;
				bulletArray[counter].SetShot(false);
			} else if (bulletArray[counter].GetCollider().checkCollision(player_1.GetCollider(), 0.1f)) {
				if (bulletArray[counter].GetColor() == sf::Color::Red) {
					player_1.SetFire(true); 
				} else if (bulletArray[counter].GetColor() == sf::Color::Blue) {
					player_1.SetFreeze(true); 
				} else if (bulletArray[counter].GetColor() == sf::Color::Yellow) {
					player_1.SetSlow(true); 
				} else if (bulletArray[counter].GetColor() == sf::Color::Green) {
					player_1.SetHealth(player_1.GetHealth() - 1);
				}
				std::cout << "Player 1 's health : " << player_1.GetHealth() << std::endl;
				bulletArray[counter].SetShot(false);
			}
			if (!bulletArray[counter].GetShot()) {
				window.draw(bulletArray[counter].body);
			}
			counter++;
		}
		window.display();
	}
}