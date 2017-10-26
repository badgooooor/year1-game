#include "hud.h"
#include <SFML\Graphics.hpp>

Hud::Hud()
{
	// Set font.
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	// Initialize the font.
	player_1_text.setFont(font);
	player_1_text.setString("0");
	player_1_text.setCharacterSize(24);
	player_1_text.setFillColor(sf::Color::Blue);
	player_1_text.setPosition(40.0f, 40.0f);

	player_2_text.setFont(font);
	player_2_text.setString("0");
	player_2_text.setCharacterSize(24);
	player_2_text.setFillColor(sf::Color::Red);
	player_2_text.setPosition(70.0f, 40.0f);

	resultText.setFont(font);
	resultText.setCharacterSize(24);
	resultText.setFillColor(sf::Color::Green);
	resultText.setPosition(400.0f, 400.0f);
}


Hud::~Hud()
{
}

// Text-drawing method.
void Hud::Draw(sf::RenderWindow & window)
{
	window.draw(player_1_text);
	window.draw(player_2_text);
}

void Hud::ChangeScore(unsigned int player, unsigned int score)
{
	switch (player) {
		case 1:
			player_1_text.setString(score + '0');
			break;
		case 2:
			player_2_text.setString(score + '0');
			break;
	}
}

void Hud::DrawResultText(sf::RenderWindow & window)
{
	window.draw(resultText);
}

void Hud::SetResultText(unsigned int state)
{
	switch(state) {
		case 1 :
			resultText.setString("Player 1 Win this round.");
			break;
		case 2 :
			resultText.setString("Player 2 Win this round.");
			break;
		case 3 :
			resultText.setString("Player 1 Win This game.");
			break;
		case 4 :
			resultText.setString("Player 2 Win This game.");
			break;
	}
}
